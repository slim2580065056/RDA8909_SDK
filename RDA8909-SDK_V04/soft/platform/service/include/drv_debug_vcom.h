/* Copyright (C) 2016 RDA Technologies Limited and/or its affiliates("RDA").
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

#ifndef _DRV_DEBUG_UART_VIRTUAL_COM_
#define _DRV_DEBUG_UART_VIRTUAL_COM_

#include <stdint.h>
#include <stdbool.h>

struct debug_vcom;
typedef struct debug_vcom dvc_t;

typedef enum
{
    DVC_RX_ARRIVED = (1 << 0),
    DVC_RX_OVERFLOW = (1 << 1),
} dvcEvent_t;

typedef void (*dvcEventCb_t) (dvc_t *d, dvcEvent_t event, unsigned long param);

struct debug_vcom_config
{
    uint32_t rx_fifo_size;
    uint32_t tx_fifo_size;
    dvcEvent_t evt_mask;
    dvcEventCb_t callback;
    unsigned long param;
};

typedef struct debug_vcom_config dvcCfg_t;

dvc_t *dvcCreate(const dvcCfg_t *cfg);
void dvcDestroy(dvc_t *d);
bool dvcOpen(dvc_t *d);
void dvcClose(dvc_t *d);
ssize_t dvcRead(dvc_t *d, void *buf, size_t size);
ssize_t dvcWrite(dvc_t *d, const void *data, size_t size);

#endif // _DRV_DEBUG_UART_VIRTUAL_COM_
