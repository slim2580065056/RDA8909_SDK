#include "cos_log.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "drv.h"
#include "vfs.h"

#include "hal_gpio.h"
#include "hal_i2c.h"
#include "hal_uart.h"

#include "ext_device.h"
#include "ext_sys.h"

#include "app.h"
#include "device_uart.h"
#include "unit.h"

#if 1
//==================================================
// app log to uart function
//==================================================
static DEVICE_T *uart_dev;

void print_log_init(void)
{
    DEVICE_UART_CONFIG_T uartcfg;
    uartcfg.id = 1;
    uartcfg.baud = 9600;
    uartcfg.ctsEnabled = FALSE;
    uartcfg.rtsEnabled = FALSE;
    uartcfg.autoBaudLC = FALSE;
    uart_dev = UartCreate(&uartcfg, 0);
    uart_dev->open(uart_dev);
}

void print_log_close(void)
{
    uart_dev->close(uart_dev);
}

void print_log(const char *fmt, ...)
{
    char buf[1024];
    int length = 0;
    va_list ap;

    va_start(ap, fmt);
    length = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    uart_dev->write(uart_dev, (const uint8_t *)buf, (unsigned)length);
}

#else
//==================================================
// app log to file function
//==================================================
static int print_log_fd = -1;
int print_log_init()
{
    if (print_log_fd < 0) {
        print_log_fd = vfs_open("app_log.txt", O_WRONLY | O_CREAT);
    }
    return print_log_fd >= 0 ? 0: -1;
}

void print_log_close()
{
    if (print_log_fd >= 0) {
        vfs_close(print_log_fd);
        print_log_fd = -1;
    }
}

void print_log(const char *fmt, ...)
{
    char buf[1024];
    va_list ap;

    if (print_log_fd < 0)
        return;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    vfs_write(print_log_fd, buf, strlen(buf));
}
#endif
