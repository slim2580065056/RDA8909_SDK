#ifndef __EXT_SYS__
#define __EXT_SYS__

#include "stddef.h"

/* get signal RSSI */
int ext_sys_getRSSI(void);

/* get registration state */
int ext_sys_getState(void);

/* get activate state */
int ext_sys_getActState(void);

/* get operater name */
bool ext_sys_getOper(byte *pBuf, size_t size);

#endif // __EXT_SYS__
