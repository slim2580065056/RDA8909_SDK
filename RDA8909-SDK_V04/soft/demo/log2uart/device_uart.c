/* Copyright (C) 2017 RDA Technologies Limited and/or its affiliates("RDA").
* All rights reserved.
*
* This software is supplied "AS IS" without any warranties.
* RDA assumes no responsibility or liability for the use of the software,
* conveys no license or title under any patent, copyright, or mask work
* right to the product. RDA reserves the right to make changes in the
* software without notification.  RDA also make no representation or
* warranty that such application will be suitable for the specified use
* without further testing or modification.
*/

// #define LOCAL_LOG_LEVEL LOG_LEVEL_VERBOSE

#define LOCAL_LOG_TAG MAKE_LOG_TAG('M', 'Y', 'A', 'P')
#include "cos_log.h"
#include "cos.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "drv.h"
#include "hal_uart.h"
#include "hal_gpio.h"
#include "hal_sys.h"
#include "hal_timers.h"

#include "device_uart.h"

#define XCPU_CACHE_LINE_SIZE (16)
#define XCPU_CACHE_LINE_MASK (XCPU_CACHE_LINE_SIZE - 1)

#define UART_RX_DMA_SIZE (256)
#define UART_RX_BUF_SIZE (4 * 1024)
#define UART_TX_BUF_SIZE (4 * 1024)
#define UART_RX_POLL_PERIOD (15) // ms

#define UART_WAIT_TX_DONE_TIMEOUT (500)

#define UART_POOL_SIZE (UART_RX_DMA_SIZE + UART_RX_BUF_SIZE + UART_TX_BUF_SIZE + XCPU_CACHE_LINE_SIZE)

typedef struct
{
    DEVICE_T ops; // API
    DRV_UART_T *drv;
    DEVICE_UART_CONFIG_T config; // UART configuration

    bool sleep; // whether in sleep
    COS_CALLBACK_FUNC_T registered_func;
} DEVICE_UART_T;

static void UartDestroy(DEVICE_T *th);
static bool UartOpen(DEVICE_T *th);
static void UartClose(DEVICE_T *th);
static int UartWrite(DEVICE_T *th, const uint8_t *data, unsigned length);
static int UartRead(DEVICE_T *th, uint8_t *data, unsigned size);
static void UartSleep(DEVICE_T *th, bool wakeupEnabled);
static void UartWakeup(DEVICE_T *th);
static bool UartIsBaudSupported(DEVICE_T *th, int baud);
static void UartCallback(DRV_UART_T *drv, void *param, DRV_UART_EVENT_T evt);
static bool UartSetFlowCtrl(DEVICE_T *th, uint8_t rxfc, uint8_t txfc);
static void UartSetFormat(DEVICE_T *th, int baud);

static void UartDrvFormat(DRV_UART_CFG_T *cfg)
{
    cfg->dataBits = DRV_UART_DATA_BITS_8;
    cfg->stopBits = DRV_UART_STOP_BITS_1;
    cfg->parity = DRV_UART_NO_PARITY;
}

VOID uart_register_rx_cb(DEVICE_T *th, COS_CALLBACK_FUNC_T callfunc)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)th;

    uart->registered_func = callfunc;
}

// =============================================================================
// UartCreate
// =============================================================================
DEVICE_T *UartCreate(DEVICE_UART_CONFIG_T *cfg, uint8_t devno)
{
    // assert(cfg != NULL)
    unsigned drvsize = DRV_UartStructSize();
    unsigned memsize = sizeof(DEVICE_UART_T) + UART_POOL_SIZE + drvsize;
    DEVICE_UART_T *uart = (DEVICE_UART_T *)COS_MALLOC(memsize);
    memset(uart, 0, sizeof(*uart));

    uart->drv = (DRV_UART_T *)((uint32_t)uart + sizeof(*uart));
    uint32_t rxDmaBuf = ((uint32_t)uart->drv + drvsize + XCPU_CACHE_LINE_MASK) & ~XCPU_CACHE_LINE_MASK;
    uint32_t rxBuf = rxDmaBuf + UART_RX_DMA_SIZE;
    uint32_t txBuf = rxBuf + UART_RX_BUF_SIZE;

    uart->config = *cfg;
    COS_LOGI(0, "UART%d create: baud/%d", uart->config.id, cfg->baud);

    uart->ops.devno = devno;
    uart->ops.destroy = UartDestroy;
    uart->ops.open = UartOpen;
    uart->ops.close = UartClose;
    uart->ops.write = UartWrite;
    uart->ops.read = UartRead;
    uart->ops.sleep = UartSleep;
    uart->ops.wakeup = UartWakeup;
    uart->ops.isBaudSupported = UartIsBaudSupported;
    uart->ops.setFlowCtrl = UartSetFlowCtrl;
    uart->ops.setFormat = UartSetFormat;

    DRV_UART_CFG_T drvcfg = {0};
    drvcfg.baud = cfg->baud;
    UartDrvFormat(&drvcfg);
    drvcfg.ctsEnabled = cfg->ctsEnabled;
    drvcfg.rtsEnabled = cfg->rtsEnabled;
    drvcfg.autoFlowCtrlLevel = drvcfg.rtsEnabled ? DRV_UART_DEFAULT_AUTO_FLOW_CTRL_LEVEL : DRV_UART_DISABLE_AUTO_FLOW_CTRL;
    drvcfg.autoBaudLC = cfg->autoBaudLC;
    drvcfg.forceDivider = 0;
    drvcfg.rxDmaBuf = (uint8_t *)HAL_SYS_GET_UNCACHED_ADDR(rxDmaBuf);
    drvcfg.rxBuf = (uint8_t *)rxBuf;
    drvcfg.txBuf = (uint8_t *)HAL_SYS_GET_UNCACHED_ADDR(txBuf);
    drvcfg.rxDmaSize = UART_RX_DMA_SIZE;
    drvcfg.rxBufSize = UART_RX_BUF_SIZE;
    drvcfg.txBufSize = UART_TX_BUF_SIZE;
    drvcfg.rxPollPeriod = UART_RX_POLL_PERIOD;
    drvcfg.evtMask = DRV_UART_RX_ARRIVED | DRV_UART_WAKE_UP;
    drvcfg.callback = UartCallback;
    drvcfg.callbackParam = uart;
#ifdef AT_UART_LPS_SUPPORT
    drvcfg.lpsOn = true;
#endif

    DRV_UartInit(uart->drv, uart->config.id, &drvcfg);
    return (DEVICE_T *)uart;
}

// =============================================================================
// UartDestroy
// =============================================================================
static void UartDestroy(DEVICE_T *th)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)th;

    if (uart == NULL)
        return;

    COS_LOGI(0, "UART%d destroy", uart->config.id);
    DRV_UartClose(uart->drv, true);
    COS_FREE(uart);
}

// =============================================================================
// Sleep
// =============================================================================
static void UartSleep(DEVICE_T *th, bool wakeupEnabled)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)th;
    if (uart->sleep)
        return;

    COS_LOGI(0, "UART%d sleep", uart->config.id);
    DRV_UartSleep(uart->drv, false, wakeupEnabled);
    uart->sleep = true;
}

// =============================================================================
// Wakeup
// =============================================================================
static void UartWakeup(DEVICE_T *th)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)th;
    if (!uart->sleep)
        return;

    COS_LOGI(0, "UART%d wakeup", uart->config.id);
    DRV_UartWakeup(uart->drv);
    uart->sleep = false;
}

// =============================================================================
// Write
// =============================================================================
static int UartWrite(DEVICE_T *th, const uint8_t *data, unsigned length)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)th;

    if (data == NULL || length == 0)
        return 0;

    COS_LOGI(0, "UART%d write: len=%d", uart->config.id, length);
    if (uart->sleep)
    {
        COS_LOGW(0, "UART%d skip output due to wakeup fail", uart->config.id);
        return 0;
    }

    int trans = DRV_UartWrite(uart->drv, data, length, UART_WAIT_TX_DONE_TIMEOUT);
    if (trans < 0)
        COS_LOGE(0, "UART%d output error %d", uart->config.id, trans);
    else if (trans < length)
        COS_LOGE(0, "UART%d output overflow, drop %d bytes", uart->config.id, length - trans);
    return trans;
}

//extern HANDLE task_handle;
static void UartCallback(DRV_UART_T *drv, void *param, DRV_UART_EVENT_T evt)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)param;
    COS_LOGI(0, "UART%i callback evt is 0x%08x", uart->config.id, evt);

    if (evt & (DRV_UART_RX_ARRIVED | DRV_UART_WAKE_UP))
    {
//        DeviceScheduleRead((DEVICE_T *)uart);
        //if (uart->registered_func != NULL)
            //COS_TaskCallbackNotif(task_handle, uart->registered_func, uart);
    }
}

// =============================================================================
// Read
// =============================================================================
static int UartRead(DEVICE_T *th, uint8_t *data, unsigned size)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)th;
    if (uart->sleep)
        return 0;
    if (data == NULL || size == 0)
        return 0;

    int trans = DRV_UartRead(uart->drv, data, size);
    if (trans < 0)
        COS_LOGE(0, "UART%d read error %d", uart->config.id, trans);
    else
        COS_LOGE(0, "UART%d read %d, got %d", uart->config.id, size, trans);
    return trans;
}

// =============================================================================
// Open
// =============================================================================
static bool UartOpen(DEVICE_T *th)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)th;

    COS_LOGI(0, "UART%d open", uart->config.id);
    DRV_UartOpen(uart->drv);
    uart->sleep = false;
    return true;
}

// =============================================================================
// Close
// =============================================================================
static void UartClose(DEVICE_T *th)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)th;

    COS_LOGI(0, "UART%d close", uart->config.id);
    DRV_UartClose(uart->drv, false);
    uart->sleep = true;
}

// =============================================================================
// Check whether baud rate is supported. Ideally, it shoule be integrated with
// =============================================================================
static bool UartIsBaudSupported(DEVICE_T *th, int baud)
{
    static const int list[] = {0, 1200, 2400, 4800, 9600, 14400, 19200,
                               28800, 33600, 38400, 57600, 115200,
                               230400, 460800, 921600};
    for (int n = 0; n < ARRAY_SIZE(list); n++)
        if (baud == list[n])
            return true;
    return false;
}

// =============================================================================
// Set flow control
// =============================================================================
static bool UartSetFlowCtrl(DEVICE_T *th, uint8_t rxfc, uint8_t txfc)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)th;
    COS_LOGI(0, "UART%d set flow ctrl %d/%d", uart->config.id, rxfc, txfc);

    DRV_UartWaitTxFinish(uart->drv, UART_WAIT_TX_DONE_TIMEOUT);
    DRV_UartClose(uart->drv, true);

    DRV_UART_CFG_T drvcfg = DRV_UartGetCfg(uart->drv);
    uart->config.rtsEnabled = drvcfg.rtsEnabled = rxfc;
    uart->config.ctsEnabled = drvcfg.ctsEnabled = txfc;
    drvcfg.autoFlowCtrlLevel = drvcfg.rtsEnabled ? DRV_UART_DEFAULT_AUTO_FLOW_CTRL_LEVEL : DRV_UART_DISABLE_AUTO_FLOW_CTRL;
    DRV_UartInit(uart->drv, uart->config.id, &drvcfg);
    DRV_UartOpen(uart->drv);
    return true;
}

// =============================================================================
// Set baud, format and parity
// =============================================================================
static void UartSetFormat(DEVICE_T *th, int baud)
{
    DEVICE_UART_T *uart = (DEVICE_UART_T *)th;
    COS_LOGI(0, "UART%d change format baud=%d",
              uart->config.id, baud);

    DRV_UartWaitTxFinish(uart->drv, UART_WAIT_TX_DONE_TIMEOUT);
    DRV_UartClose(uart->drv, true);

    uart->config.baud = baud;

    DRV_UART_CFG_T drvcfg = DRV_UartGetCfg(uart->drv);
    drvcfg.baud = uart->config.baud;
    UartDrvFormat(&drvcfg);
    DRV_UartInit(uart->drv, uart->config.id, &drvcfg);
    DRV_UartOpen(uart->drv);
}

