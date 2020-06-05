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

#ifndef _HAL_CLK_32K_H_
#define _HAL_CLK_32K_H_

#include <stdint.h>

// =============================================================================
//  MACROS
// =============================================================================
#define CLK_32K_SRC_RC      0
#define CLK_32K_SRC_XTAL    1
#define CLK_32K_SRC_26MXTAL 2

#define NO_CLK_32K_SRC 0xffffffff

/*
We strongly suggest you calling hal_Src32kEnable when you wanna change 32k clk source,
instead of config register of PMU directly.

Usually,you only need these two API(hal_Src32kEnable and hal_GetCurrentSrc32k),except Lps module,
because each 32k source has its own lps_rate.
Lps module has to set lps_rate for each 32k clk source by TCU/LPS calibration after power on,
and they are used when skip frame
*/

void hal_Src32kEnable(UINT32 src_32k);

//return value is either CLK_32K_SRC_RC or CLK_32K_SRC_XTAL or CLK_32K_SRC_26MXTAL
UINT32 hal_GetCurrentSrc32k(VOID);
UINT32 hal_GetLpsRate(UINT32 src_32k);
void hal_SetLpsRate(UINT32 src_32k, UINT32 lpsRate);
void hal_Src32kInit();

/* return NO_CLK_32K_SRC if all calibrated */
UINT32 hal_GetUnCalibSrc();

void hal_set_32k_lpsRate(UINT32 rate);
UINT32 hal_get_32k_lpsRate();
#endif //_HAL_LPS_H_
