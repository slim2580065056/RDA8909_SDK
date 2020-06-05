#ifndef _NET_API_H
#define _NET_API_H

#include "cfw.h"
#include "cfw_nv.h"
#include "stddef.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"

struct netif *getGprsNetIf(UINT8 nSim,UINT8 nCid);
struct netif *getEtherNetIf(UINT8 nCid);
UINT8 startGprsLink(UINT8 *apn,UINT8 nSIMID);

#ifdef WIFI_SUPPORT
struct netif * startWifiLink(UINT8 *ssid,UINT8 *password); 
#endif
void lwipTestEntry(UINT8 test_index, UINT8 isStart);
int IN6_IS_ADDR_V4MAPPED(const struct in6_addr *addr);
int sockaddr_cmp(struct sockaddr *x, struct sockaddr *y);
struct netif *ip4_src_route(const ip4_addr_t *dst, const ip4_addr_t *src);

bool getSimIccid(uint8_t simId, uint8_t *simiccid, uint8_t *len);
bool getSimImei(uint8_t simId, uint8_t *imei, uint8_t *len);
bool getSimImsi(uint8_t simId,uint8_t *imsi, uint8_t *len);

#endif

