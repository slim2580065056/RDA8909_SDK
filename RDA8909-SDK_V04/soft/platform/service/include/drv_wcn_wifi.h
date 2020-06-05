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

#ifndef _DRV_WCN_WIFI_H_
#define _DRV_WCN_WIFI_H_

#include <stdint.h>

typedef struct wifi_ap_info
{
    uint32_t bssid_low;     ///< mac address low
    uint16_t bssid_high;    ///< mac address high
    uint8_t channel;        ///< channel id
    uint8_t rssival;        ///< signal strength
} wifiApInfo_t;

typedef struct wifi_scan_request
{
    uint32_t max_aps;       ///< caller set, the maximum aps can be stored
    uint32_t found_aps;     ///< found aps
    wifiApInfo_t *aps;      ///< buffer to store aps
    void *param;            ///< caller set user data
    void (*complete) (struct wifi_scan_request *req);   ///< caller set, will be called after scan done
} wifiScanReq_t;

/**
 * @brief scan all wifi channels
 *
 * @param max_round     scan <max_round> rounds
 * @param req           wifi scan request
 * @return
 *      - (-1)  fail
 *      - 0     success
 */
int drvWifiScanAllChannel(uint32_t max_round, wifiScanReq_t *req);

/**
 * @brief scan specific channel
 *
 * @param channel   the ap channel
 * @param req       wifi scan request
 * @param timeou_ms max scan times in millisecond
 *      - (-1)  fail
 *      - 0     success
 */
int drvWifiScanChannel(uint32_t channel, wifiScanReq_t *req, uint32_t timeout_ms);

#endif // _DRV_WCN_WIFI_H_
