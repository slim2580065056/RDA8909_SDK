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

#ifndef __SXS_RMT_H__
#define __SXS_RMT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sxs_type.h"

typedef void (*userRmcProc_t) (u8 id, u8 *data, u16 size, unsigned long p);

void sxs_RegUserRmc(userRmcProc_t proc, unsigned long p);

// =============================================================================
// sxs_RmtInit
// -----------------------------------------------------------------------------
/// Data exchange with remote computer initialization.
// =============================================================================
void sxs_RmtInit(bool fullInit);

void sxs_PrcsRmtData(u8 Id, u8 *Data, u16 Length);

// =============================================================================
// sxs_SetFnStamp
// -----------------------------------------------------------------------------
/// Start trace time stamping.
/// @param FnStamp   Address of the frame number stamp.
/// @param RmtCpuIdx Remote CPU index.
// =============================================================================
void _sxs_SetFnStamp(u32 *FnStamp, u8 RmtCpuIdx);

#define sxs_SetFnStamp(a) _sxs_SetFnStamp(a, 0)

#ifdef __cplusplus
}
#endif

#endif

/// @} // <-- End of sx_rmt group
