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

#ifndef _SPIFFS_VFS_H_
#define _SPIFFS_VFS_H_

typedef struct
{
    unsigned phys_start;
    unsigned phys_size;
    unsigned phys_erase_block; // 0 for default (4K)
    unsigned log_block_size;   // 0 for default (4K)
    unsigned log_page_size;    // 0 for default (256). only 256 is verified
    unsigned fd_cache_count;
    bool format_on_fail;
    bool check_after_mount;
} spiffs_mount_opt_t;

int spiffs_vfs_mount(const char *base_path, const spiffs_mount_opt_t *opt);

#endif
