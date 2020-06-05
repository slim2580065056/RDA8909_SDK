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

#ifndef _HAL_WCN_H_
#define _HAL_WCN_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_CHANNEL_IDX (13)

typedef struct
{
    // BSSID
    uint32_t bssidAddrLow;
    uint32_t bssidAddrHigh;

    // rssiVal
    uint8_t rssiVal;

    uint8_t channel;
} wlanInfo_t;

void hal_WcnWlanIrqHandler(uint8_t intId);
void hal_WcnOscIrqHandler(uint8_t intId);

void hal_WlanOpen();
void hal_WlanClose();
void hal_WlanSetChannel(uint8_t channel);
void hal_WlanReadInfo(wlanInfo_t *info);
bool hal_WlanDataReady();
void hal_WlanClearReady();

void hal_BTOpen();
void hal_BTClose();

void hal_WcnOpen();
void hal_WcnClose();

void hal_WcnSuspend();
void hal_WcnResume();

#endif
