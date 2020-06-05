#ifndef __EXT_DEVICE__
#define __EXT_DEVICE__

#include "stddef.h"

/* see AT+GMI */
bool ext_device_getGMI(byte *pBuf, size_t size);

/* see AT+GMM */
bool ext_device_getGMM(byte *pBuf, size_t size);

/* see AT+GMR */
bool ext_device_getGMR(byte *pBuf, size_t size);

/* Get device IMEI */
bool ext_device_getIMEI(byte *pBuf, size_t size);

/* Get SIM IMSI */
bool ext_device_getIMSI(byte *pBuf, size_t size);

/* Get SIM ICCID */
bool ext_device_getICCID(byte *pBuf, size_t size);

/* power off device */
bool ext_device_poweroff();

/* reboot device */
bool ext_device_reboot();

#endif // __EXT_DEVICE__
