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

#ifndef _BLOCK_DEVICE_H_
#define _BLOCK_DEVICE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct block_device_s;
typedef struct block_device_s block_device_t;

typedef struct
{
    int (*read)(block_device_t *dev, uint64_t nr, int count, void *buf);
    int (*write)(block_device_t *dev, uint64_t nr, int count, const void *data);
    int (*erase)(block_device_t *dev, uint64_t nr, int count);
    void (*destroy)(block_device_t *dev);
} block_device_ops_t;

struct block_device_s
{
    block_device_ops_t ops;
    int block_size;
    uint64_t block_count;
    void *priv;
};

int bdev_read(block_device_t *dev, uint64_t nr, int count, void *buf);
int bdev_write(block_device_t *dev, uint64_t nr, int count, const void *data);
int bdev_erase(block_device_t *dev, uint64_t nr, int count);
void bdev_destroy(block_device_t *dev);

int register_umss_bdev(block_device_t *bdev);
void unregister_umss_bdev(int dev_no);
#ifdef __cplusplus
}
#endif

#endif