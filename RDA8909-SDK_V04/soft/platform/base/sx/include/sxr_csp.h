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

#ifndef __SXR_CSP_H__
#define __SXR_CSP_H__

#include "chip_id.h"

#ifndef SXR_CSP_TK_STCK_HEAP
#error "Location for task stack heap must be defined"
#endif
#ifndef SXR_CSP_JB_STCK_HEAP
#error "Location for job stack heap must be defined"
#endif
#ifndef SXR_CSP_JB_CTX_HEAP
#error "Location for job context heap must be defined"
#endif

#include "hal_mem_map.h"
#include "hal_trace.h"
#include "hal_timers.h"
#include "hal_sys.h"
#include "hal_sxr.h"

#define SXS_BOOT_DIAG_AREA HAL_HEAP_START(0)

#define sxr_Reset(a) hal_SysRestart()
#define sxr_EnterSc() hal_SysEnterCriticalSection()
#define sxr_ExitSc(a) hal_SysExitCriticalSection(a)

#define SXS_GET_RA(a) HAL_SYS_GET_RA(a)
#define SXS_GET_SP(a) HAL_SYS_GET_SP(a)

#define pal_WDogCntRst() hal_TimWatchDogKeepAlive()
#define pal_SoftAbort() hal_SoftAbort()
#define pal_SoftBreak() asm volatile("break 2\n" \
                                     "nop\n"     \
                                     "nop\n"     \
                                     "nop\n")

#define pal_SetIrqSpy(IrqId, Start)
#define pal_SetTaskSpy(TskNb) hal_DbgPxtsProfileTask(HAL_DBG_PXTS_SX, TskNb)

#define PAL_NB_RAM_AREA HAL_NB_RAM_AREA
#define PAL_HEAP_START(area) HAL_HEAP_START(area)
#define PAL_HEAP_SIZE(area) HAL_HEAP_SIZE(area)
#define PAL_HEAP_END(area) HAL_HEAP_END(area)
#define PAL_IS_ROM(addr) HAL_IS_CODE(addr)

#define PAL_FRAMED_TIMER 1
#define PAL_REGULAR_TIMER 0
#define pal_TimerSetCnt NULL
#define pal_TimerGetCnt NULL
#define pal_TickInit() hal_TimTickOpen
#define pal_TimDelay hal_TimDelay

#define pal_TraceSendInitRmc hal_HstTraceSendInitRmc
#define pal_TraceRequestBuf hal_HstTraceRequestData
#define pal_TraceBufFilled hal_HstTraceDataFilled
#define pal_TraceSendData hal_HstTraceOutput
#define pal_TraceSetTxEnabled hal_HstTraceSetTxEnabled
#define pal_TraceSetRxEnabled hal_HstTraceSetRxEnabled
#define pal_TraceSetFnStamp hal_HstTraceSetFnStamp
#define pal_TraceTxFlush hal_HstTraceTxFlush
#define pal_TraceSetRxProc hal_hstTraceSetRxProc
#define pal_TraceGetBufferHead hal_HstTraceGetBufferHead

#endif
