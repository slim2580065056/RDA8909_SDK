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

#ifndef _APP_LOADER_H_
#define _APP_LOADER_H_

#include <stdbool.h>

#define FLASH_EXTAPP_BASE 0x88340000

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int (*enter)(char argc, char **argv);
    void (*exit)(void);
} appImageHandler_t;

bool appLoadFromMem(const void *address, appImageHandler_t *handler);

#ifdef __cplusplus
}
#endif
#endif
