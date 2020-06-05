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

#ifndef _COS_H_
#define _COS_H_

#include "cs_types.h"
#include "cos_log.h"

#ifdef __cplusplus
extern "C" {


// =============================================================================
// TRACE related macros
// -----------------------------------------------------------------------------
/// The roughest method is COS_OUTPUT.
/// * It will be formatted on target (not on PC)
/// * It is not affected by LOCAL_LOG_LEVEL
/// * It is not affected by PC trace level control
/// * It will be output as SXR/16, or specified by LOCAL_LOG_ID
/// It shouldn't be used by release codes, but is convenient for quick try.
///
/// Detail concepts:
/// * Target format and PC format: Target formatting will consume cycles. So
///   the better method is to formatted on PC
/// * String on PC format: At PC format, string and integer are handled
///   differently. For string, target shall calculate the string length and
///   send the string. For integer, target shall only send 4 bytes. TSM(...)
///   macro shall be used to indicate string argument location (start from 0).
/// * Compile time control: Code size is important. LOCAL_LOG_LEVEL can be used
///   to control trace at compile time. By default, levels above LOG_LEVEL_INFO
///   will be output. To enable more verbose output, it is needed to modify
///   codes by define LOCAL_LOG_LEVEL.
/// * Runtime control: At running, PC can send command to enable/disable output
///   by id (TID/TLEVEL). It can't save code size, but can save some cycles and
///   output bandwidth.
///
/// Limitation:
/// * For PC format, at most 7 arguments can be supported.
/// * For target format, the formatted string length is limited to 256.
/// * TODO: There are no macros for trace with DB now.
///
/// Macros:
/// * TSM(...)/TSMALL: String indicators.
/// * COS_TRACE_E/W/I/D/V: PC format trace.
/// * COS_PRINTF_E/W/I/D/V: Target format trace.
/// * COS_DUMP/16/32: Dump macro, and set format.
/// * COS_OUTPUT: (dirty) Forced output trace, target format.
// =============================================================================

















#endif // !__RESOURCE_GEN_

#define COS_CREATE_DEFAULT 0
#define COS_CREATE_SUSPENDED (1 << 0)

typedef struct _TASK_HANDLE TASK_HANDLE;

typedef enum {
    COS_MMI_HEAP = 0x00,
    COS_HEAP_COUNT
} COS_HEAP_ID;

#define COS_MMI_TASKS_PRIORITY_BASE 220 // 220-250 is assigned to MMI part.
#define COS_PRIORITY_NUM 30

unsigned COS_Msec2Tick(unsigned ms);
unsigned COS_Sec2Tick(unsigned sec);
unsigned COS_Tick2Msec(unsigned tick);
unsigned COS_GetTickCount(void);

typedef VOID (*PTASK_ENTRY)(PVOID pParameter);

HANDLE COS_CreateTask(PTASK_ENTRY pTaskEntry,
                      PVOID pParameter,
                      PVOID pStackAddr,
                      UINT16 nStackSize,
                      UINT8 nPriority,
                      UINT16 nCreationFlags,
                      UINT16 nTimeSlice,
                      PCSTR pTaskName);
HANDLE COS_CreateTask_Prv(PTASK_ENTRY pTaskEntry,
                          PVOID pParameter,
                          PVOID pStackAddr,
                          UINT16 nStackSize,
                          UINT8 nPriority,
                          UINT16 nCreationFlags,
                          UINT16 nTimeSlice,
                          PCSTR pTaskName) DEPRECATED;
VOID COS_StartTask(TASK_HANDLE *pHTask, PVOID pParameter);
VOID COS_StopTask(TASK_HANDLE *pHTask);
BOOL COS_DeleteTask(HANDLE hTask);
BOOL COS_SuspendTask(HANDLE hTask);
BOOL COS_ResumeTask(HANDLE hTask);
HANDLE COS_GetCurrentTaskHandle(void);

typedef struct _COS_EVENT
{
    UINT32 nEventId;
    UINT32 nParam1;
    UINT32 nParam2;
    UINT32 nParam3;
} COS_EVENT;

#define COS_WAIT_FOREVER 0xFFFFFFFF
#define COS_NO_WAIT 0x0

#define COS_EVENT_PRI_NORMAL 0
#define COS_EVENT_PRI_URGENT 1

// NOTE: timeout is not implemented
BOOL COS_SendEvent(HANDLE hTask, COS_EVENT *pEvent, UINT32 nTimeOut, UINT16 nOption);
BOOL COS_WaitEvent(HANDLE hTask, COS_EVENT *pEvent, UINT32 nTimeOut);

UINT32 COS_TaskMailBoxId(HANDLE hTask) DEPRECATED;
UINT32 COS_TaskEventCount(HANDLE hTask);
BOOL COS_ResetEventQueue(HANDLE hTask) DEPRECATED;
BOOL COS_IsEventAvailable(HANDLE hTask);
BOOL COS_FreeEnvCountAvail(UINT32 count) DEPRECATED;

// =============================================================================
// COS_Assert
// -----------------------------------------------------------------------------
/// Trigger breakpoint/gdb if condition is FALSE (both debug and release version).
/// COS_Assert(0, "") will panic forcedly. The assert message can be shown by
/// coolwatcher.
// =============================================================================
void COS_Assert(BOOL expected, const char *format, ...);

// =============================================================================
// COS_CALLBACK_FUNC_T
// -----------------------------------------------------------------------------
/// Function pointer type for a typical callback.
// =============================================================================
typedef VOID (*COS_CALLBACK_FUNC_T)(void *param);

// =============================================================================
// Task Callback
// -----------------------------------------------------------------------------
/// Run callback in task at next event loop, with one parameters.
/// They are implemented with EVENT, and the callback will be executed in
/// COS_WaitEvent. They are easier to be used that COS_SendEvent due to it is
/// not needed to define EVENT ID, and it is not needed to expose functions
/// to event loop.
///
/// In case that the callback is droppable, and it maybe sent frequently,
/// COS_TaskCallbackNotif will remove previous ones in queue before send.
/// ATTENTION: remove previous ones will take time, don't call it in ISR.
// =============================================================================
BOOL COS_IsTaskCallbackSet(HANDLE hTask, COS_CALLBACK_FUNC_T callback, void *param);
BOOL COS_TaskCallback(HANDLE hTask, COS_CALLBACK_FUNC_T callback, void *param);
BOOL COS_TaskCallbackNotif(HANDLE hTask, COS_CALLBACK_FUNC_T callback, void *param);
BOOL COS_StopTaskCallback(HANDLE hTask, COS_CALLBACK_FUNC_T callback, void *param);

// =============================================================================
// SYNC callback
// -----------------------------------------------------------------------------
/// Run callback in task at next event loop, with one parameters. And it will
/// wait the callback is executed. When the target task is current task,
/// the callback will be called directly.
///
/// callback can be NULL. It can be used to wait all previous events are handled
/// in the target task.
// =============================================================================
BOOL COS_TaskCallbackSync(HANDLE hTask, COS_CALLBACK_FUNC_T callback, void *param);
BOOL COS_TaskWaitEventHandled(HANDLE hTask);

BOOL COS_TaskChangePriority(HANDLE hTask, UINT8 priority);
// =============================================================================
// Callback Timer
// -----------------------------------------------------------------------------
/// Run callback in task after specified period. They are implemented with TIMER,
/// and the callback will be executed in COS_WaitEvent. They are easier to be
/// used that COS_StartTimer due to it is not needed to define timer ID, and it
/// is not needed to expose functions to event loop.
///
/// Flags:
/// * FORCEDLY/CHECK: normally, existed timer will be removed before start.
///         When FORCEDLY is set, existed timer won't be checked. When CHECK is
///         is set, start timer only if the timer is not existed. These 2 flags
///         shouldn't be set simultanuously.
/// * PM1/PM3: normally, timer will be ignored in PM1 and PM3. If timer timeout
///         is really needed, these 2 flags will enable timer timeout even in
///         PM1/PM3. These 2 flags can be set simultanuously.
// =============================================================================
#define COS_TIMER_FLAG_START_FORCEDLY (1 << 0)
#define COS_TIMER_FLAG_START_CHECK (1 << 1)
#define COS_TIMER_FLAG_PM1 (1 << 8)
#define COS_TIMER_FLAG_PM3 (1 << 9)

BOOL COS_IsCallbackTimerSet(HANDLE hTask, COS_CALLBACK_FUNC_T callback, void *param);
BOOL COS_StartCallbackTimer(HANDLE hTask, UINT32 ms, COS_CALLBACK_FUNC_T callback, void *param);
BOOL COS_StartCallbackFlagTimer(HANDLE hTask, UINT32 ms, UINT32 flags, COS_CALLBACK_FUNC_T callback, void *param);
BOOL COS_StopCallbackTimer(HANDLE hTask, COS_CALLBACK_FUNC_T callback, void *param);

// =============================================================================
// COS_QueryTimerCallback
// -----------------------------------------------------------------------------
/// Query the timer callback.
///
/// @param hTask    Target task handle
/// @param callback Callback function to be run
/// @param param    First parameter of callback
/// @return         Remain period of the timer, 0xFFFFFFFF when not exist
// =============================================================================
UINT32 COS_QueryCallbackTimer(HANDLE hTask, COS_CALLBACK_FUNC_T callback, void *param);

// =============================================================================
// Function Timer
// -----------------------------------------------------------------------------
/// Function timer will be called inside OS timer IRQ. So, it must be "short".
// =============================================================================
BOOL COS_IsFunctionTimerSet(COS_CALLBACK_FUNC_T callback, void *param);
VOID COS_StartFunctionTimer(UINT32 ms, COS_CALLBACK_FUNC_T callback, void *param);
VOID COS_StartFunctionTimerForcedly(UINT32 ms, COS_CALLBACK_FUNC_T callback, void *param);
VOID COS_StartFunctionTimerCheck(UINT32 ms, COS_CALLBACK_FUNC_T callback, void *param);
VOID COS_StopFunctionTimer(COS_CALLBACK_FUNC_T callback, void *param);

#define COS_TIMER_MODE_SINGLE 0
#define COS_TIMER_MODE_PERIODIC 1

//
// TimerID ranges
//
#define COS_MMI_TIMER_ID_BASE 0x000
#define COS_MMI_TIMER_ID_END_ 0x3FF
#define COS_CSW_TIMER_ID_BASE 0x400
#define COS_CSW_TIMER_ID_END_ 0x4FF
#define COS_BT_TIMER_ID_BASE 0x500
#define COS_BT_TIMER_ID_END_ 0x5FF
#define COS_MDI_TIMER_ID_BASE 0x600
#define COS_MDI_TIMER_ID_END_ 0x6FF

#define CFW_AT_UTI_RANGE 32

BOOL COS_SetTimer(HANDLE hTask,
                  UINT8 nTimerId,
                  UINT8 nMode,
                  UINT32 nElapse) DEPRECATED;
BOOL COS_KillTimer(HANDLE hTask, UINT8 nTimerId) DEPRECATED;
UINT32 COS_QueryTimer(HANDLE hTask, UINT16 nTimerId) DEPRECATED;

BOOL COS_SetTimerEX(HANDLE hTask,
                    UINT16 nTimerId,
                    UINT8 nMode,
                    UINT32 nElapse);
BOOL COS_KillTimerEX(HANDLE hTask, UINT16 nTimerId);
UINT32 COS_QueryTimerEX(HANDLE hTask, UINT16 nTimerId);
BOOL COS_ForceDeliverTimerEx(HANDLE hTask, UINT16 nTimerId);

BOOL COS_Sleep(UINT32 nMillisecondes);
HANDLE COS_EnterCriticalSection(VOID);
BOOL COS_ExitCriticalSection(HANDLE hSection);

UINT32 COS_GetLastError(VOID);
VOID COS_SetLastError(UINT32 nErrCode); // per-thread error code

void COS_CleanDCache();   //asm volatile(".set noreorder\n\t .align 4\n\tcache 2,0\n\tnop\n\tnop\n\tnop\n\tjr ra\n\tnop\n\t.set reorder ")
void COS_CleanICache();   //asm volatile(".set noreorder\n\t .align 4\n\tcache 1,0\n\tnop\n\tnop\n\tnop\n\tjr ra\n\tnop\n\t.set reorder ")
void COS_CleanALLCache(); // asm volatile(".set noreorder\n\t .align 4\n\tcache 0,0\n\tnop\n\tnop\n\tnop\n\tjr ra\n\tnop\n\t.set reorder ")

#define COS_MALLOC(size) COS_Malloc((UINT32)size, COS_MMI_HEAP)
#define COS_FREE(p) COS_Free((PVOID)p)
#define COS_REALLOC(ptr, size) COS_Realloc(ptr, size)

#ifdef __mips16
#define COS_GET_RA(store) asm volatile("move $2, $31\n\tsw $2, 0(%0)" ::"d"((store)) \
                                       : "$2")
#else
#define COS_GET_RA(store) asm volatile("sw $31, 0(%0)" ::"r"((store)))
#endif

typedef struct _COS_HEAP_STATUS
{
    UINT32 nUsedSize;
    UINT32 nTotalSize;
} COS_HEAP_STATUS;

VOID COS_UpdateMemCallAdd(VOID *pMemeAddr, UINT32 nCallAdd);
UINT32 COS_GetHeapUsageStatus(COS_HEAP_STATUS *pHeapStatus, UINT8 nIdx);

PVOID COS_Malloc(UINT32 nSize, COS_HEAP_ID nHeapID);
PVOID COS_Realloc(VOID *ptr, UINT32 nSize);
BOOL COS_Free(PVOID pMemBlock);

#define COS_SHMEMMALLOC(size) COS_Malloc((UINT32)size, COS_MMI_HEAP)
#define COS_SHMEMFREE(p) COS_Free((PVOID)p)

HANDLE COS_CreateSemaphore(UINT32 nInitCount) DEPRECATED;
BOOL COS_DeleteSemaphore(HANDLE hSem) DEPRECATED;
BOOL COS_WaitForSemaphore(HANDLE hSem, UINT32 nTimeOut) DEPRECATED;
BOOL COS_ReleaseSemaphore(HANDLE hSem) DEPRECATED;

HANDLE COS_CreateMutex(void) DEPRECATED;
void COS_DeleteMutex(HANDLE mutex) DEPRECATED;
void COS_LockMutex(HANDLE mutex) DEPRECATED;
void COS_UnlockMutex(HANDLE mutex) DEPRECATED;

// =============================================================================
// COS_SEMA
// -----------------------------------------------------------------------------
/// COS_SEMA is a (limited) counting semaphore.
// =============================================================================
struct _COS_SEMA;
typedef struct _COS_SEMA COS_SEMA;
#define COS_SEMA_UNINIT \
    {                   \
    }

BOOL COS_SemaInited(COS_SEMA *sema);
VOID COS_SemaInit(COS_SEMA *sema, UINT32 init);
VOID COS_SemaTake(COS_SEMA *sema);
BOOL COS_SemaTryTake(COS_SEMA *sema, UINT32 ms);
VOID COS_SemaRelease(COS_SEMA *sema);
VOID COS_SemaDestroy(COS_SEMA *sema);

// =============================================================================
// COS_MUTEX
// -----------------------------------------------------------------------------
/// COS_MUTEX is just a mutex.
// =============================================================================
struct _COS_MUTEX;
typedef struct _COS_MUTEX COS_MUTEX;
#define COS_MUTEX_UNINIT \
    {                    \
    }

BOOL COS_MutexInited(COS_MUTEX *mutex);
VOID COS_MutexInit(COS_MUTEX *mutex);
VOID COS_MutexLock(COS_MUTEX *mutex);
BOOL COS_MutexTryLock(COS_MUTEX *mutex, UINT32 ms);
VOID COS_MutexUnlock(COS_MUTEX *mutex);
VOID COS_MutexDestroy(COS_MUTEX *mutex);

// to allow not using cos.h but sx direclty for timers
#define HVY_TIMER_IN (0xFFFFF000)

// =============================================================================
// COS_PAGE_NUM
// -----------------------------------------------------------------------------
/// Those are the 2 pages which can be protected by app
// =============================================================================
typedef enum {
    COS_PAGE_NUM_4 = 0x04,
    COS_PAGE_NUM_5 = 0x05,
} COS_PAGE_NUM;

// =============================================================================
// COS_PAGE_SPY_MODE
// -----------------------------------------------------------------------------
/// Type defining the possible Page Spy Mode
/// triggering an interrupt
// =============================================================================
typedef enum {
    COS_PAGE_NO_TRIGGER = 0,       /// No interrupt is triggered
    COS_PAGE_READ_TRIGGER = 1,     /// Triggered on reading of the protected page
    COS_PAGE_WRITE_TRIGGER = 2,    /// Triggered on writing of the protected page
    COS_PAGE_READWRITE_TRIGGER = 3 /// Triggered on reading or writing of the protected page
} COS_PAGE_SPY_MODE;

// =============================================================================
// COS_PageProtectSetup
// -----------------------------------------------------------------------------
/// This function setups a protection page
///
/// @param nPageNum Name of the page we want to configure
/// @param nMode Protection mode
/// @param nStartAddr Address of the beginning of the page
/// @param nEndAddr  End address of the page. This address is not included in
/// the page
// =============================================================================
UINT32 COS_PageProtectSetup(COS_PAGE_NUM nPageNum,
                            COS_PAGE_SPY_MODE nMode,
                            UINT32 nStartAddr,
                            UINT32 nEndAddr) DEPRECATED;

// =============================================================================
// COS_PageProtectEnable
// -----------------------------------------------------------------------------
/// Enable the protection of a given page.
///
/// @param nPageNum Page to enable
// =============================================================================
UINT32 COS_PageProtectEnable(COS_PAGE_NUM nPageNum) DEPRECATED;

// =============================================================================
// COS_PageProtectDisable
// -----------------------------------------------------------------------------
/// Disable the protection of a given page
///
/// @param nPageNum Page to disable
// =============================================================================
UINT32 COS_PageProtectDisable(COS_PAGE_NUM nPageNum) DEPRECATED;

UINT32 COS_cksum(UINT8 *addr, UINT32 length);

// =============================================================================
// INTERNAL DATA STRUCTURE, NEVER ACCESS DIRECTLY
// =============================================================================

struct _COS_SEMA
{
    UINT8 count;
    UINT8 mbx;
};

struct _COS_MUTEX
{
    UINT8 count;
    UINT8 task;
    UINT8 mbx;
};

#ifdef __cplusplus
}
#endif

#endif // H
