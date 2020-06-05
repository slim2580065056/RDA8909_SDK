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

#ifndef _SFFS_VFS_H_
#define _SFFS_VFS_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct block_device_s;
int sffsVfsMount(const char *base_path,
                 struct block_device_s *bdev,
                 size_t cache_count,
                 bool read_only);
int sffsVfsMkfs(struct block_device_s *bdev);

#ifdef __cplusplus
}
#endif

#endif
