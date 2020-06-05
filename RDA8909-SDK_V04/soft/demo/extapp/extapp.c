/* Copyright (C) 2018 RDA Technologies Limited and/or its affiliates("RDA").
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

#define LOCAL_LOG_TAG MAKE_LOG_TAG('M', 'Y', 'A', 'P')
#include "cos_log.h"
#include "cos.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "vfs.h"
#include "sockets.h"
#include "tm.h"
#include "drv.h"

#include "hal_gpio.h"
#include "hal_i2c.h"
#include "hal_spi.h"
#include "hal_uart.h"
#include "hal_ana_gpadc.h"
#include "hal_pwm.h"

#include "ext_device.h"
#include "ext_sys.h"

static VOID test_udp_rsp(void *param)
{
    COS_EVENT *pEvent = (COS_EVENT *)param;
    COS_PRINTFI("test_udp_rsp Got %u,%u,%u,%u",
          pEvent->nEventId, pEvent->nParam1, pEvent->nParam2, pEvent->nParam3);

    int uSocket = (int)pEvent->nParam1;
    UINT16 uDataSize = pEvent->nParam2;
    UINT8 *pData;
    CFW_TCPIP_SOCKET_ADDR from_addr;
    UINT32 iResult;
    INT32 fromLen = sizeof(CFW_TCPIP_SOCKET_ADDR);

    switch (pEvent->nEventId)
    {
    case EV_CFW_TCPIP_REV_DATA_IND:
        COS_PRINTFI("test_udp_rsp socket:%d, len:%d", uSocket, uDataSize);
        pData = COS_MALLOC(pEvent->nParam2 + 1);
        if (pData == NULL)
            return;
        iResult = CFW_TcpipSocketRecvfrom(uSocket, pData, uDataSize, 0, &from_addr, &fromLen);
        if (SOCKET_ERROR == iResult)
        {
        }
        else
        {
            COS_PRINTFI("test_udp_rsp: %d,%s,%hu,%d,", uSocket, inet_ntoa(from_addr.sin_addr), ntohs(from_addr.sin_port), iResult);
        }
        COS_FREE(pData);
        break;
    default:
        COS_PRINTFI("UDP unexpect asynchrous event/response %d", pEvent->nEventId);
        break;
    }
    COS_FREE(pEvent);
}

void test_socket()
{
    SOCKET sock;
    UINT32 iResult;

    sock = CFW_TcpipSocketEX(CFW_TCPIP_AF_INET,
                          CFW_TCPIP_SOCK_DGRAM, CFW_TCPIP_IPPROTO_UDP,
                          test_udp_rsp, 0);
    if (SOCKET_ERROR == sock)
    {
        return;
    }

    CFW_TCPIP_SOCKET_ADDR nDestAddr;
    nDestAddr.sin_len = sizeof(CFW_TCPIP_SOCKET_ADDR);
    nDestAddr.sin_family = CFW_TCPIP_AF_INET;
    nDestAddr.sin_port = htons(1234);
    iResult = CFW_TcpipInetAddr("121.41.100.43");
    if (IPADDR_NONE == iResult)
    {
    }
    else
    {
        static char *senddata="test1234567890";
        nDestAddr.sin_addr.s_addr = iResult;
        iResult = CFW_TcpipSocketSendto(sock, (VOID *)senddata, 10, 0, &nDestAddr, nDestAddr.sin_len);
    }
}

VOID test_timer(COS_CALLBACK_FUNC_T tm_cb, UINT32 sec)
{
    COS_StartCallbackTimer(COS_GetCurrentTaskHandle(), sec * 1000, tm_cb, 0);
}

static VOID test_timer_cb(void *param)
{
    static int count = 0;
    count++;
    COS_PRINTFI("test_timer_cb: %d", count);
    test_timer(test_timer_cb, 10);
}

int app_enter(int argc, char **argv)
{
    byte buf[32];
    bool ret;
    int n;

    COS_PRINTFI("extapp APP enter");

    if (argc == 0)
    {
        ret = ext_device_getIMEI(buf, sizeof(buf));
        if (ret)
            COS_PRINTFI("IMEI: %s", buf);

        ret = ext_device_getIMSI(buf, sizeof(buf));
        if (ret)
            COS_PRINTFI("IMSI: %s", buf);

        n = ext_sys_getRSSI();
        COS_PRINTFI("RSSI: %d", n);

        ret = ext_sys_getOper(buf, sizeof(buf));
        if (ret)
            COS_PRINTFI("OPER: %s", buf);

        test_timer(test_timer_cb, 10);

    } else if (argc == 1) {
        COS_EVENT *pEvent = (COS_EVENT *)argv;
        UINT8 nType = HIUINT8(pEvent->nParam3);
        switch (pEvent->nEventId)
        {
         case EV_CFW_GPRS_ACT_RSP:
            if (CFW_GPRS_ACTIVED == nType)
            {
                test_socket();
            }
            break;
        default:
            COS_PRINTFI("unexpect asynchrous event %d", pEvent->nEventId);
            break;
        }
    }
    return 0;
}

void app_exit(void)
{
    COS_PRINTFI("extapp APP exit");
}
