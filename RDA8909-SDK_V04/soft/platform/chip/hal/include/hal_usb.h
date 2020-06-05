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

#ifndef _HAL_USB_H_
#define _HAL_USB_H_

#include <stdint.h>
#include <stdbool.h>

/// @defgroup usb HAL USB Driver
/// This driver provide an interface to use the USB bus. You can use this
/// driver on interrupt mode (default) or polling mode with the function
/// #hal_UsbEpEnableInterrupt. The driver manage the EP0 on interrupt only
///
/// @par
/// The API allows to write or read several bytes using
/// #hal_UsbSend or #hal_UsbRecv.
///
/// @par
/// You transmit a callback function when you open the driver with #hal_UsbOpen.
/// This callback is call when the usb enum phase is finish and this function
/// must return a description of usb device
///
/// @{

// =============================================================================
// MACROS
// =============================================================================

#define HAL_USB_EP_DIRECTION 0x80

// =============================================================================
// HAL_USB_EP_DIRECTION_IN
// -----------------------------------------------------------------------------
/// This macro set the direction IN on an endpoint
// =============================================================================
#define HAL_USB_EP_DIRECTION_IN(X) ((X) | HAL_USB_EP_DIRECTION)

// =============================================================================
// HAL_USB_EP_DIRECTION_OUT
// -----------------------------------------------------------------------------
/// This macro set the direction OUT on an endpoint
// =============================================================================
#define HAL_USB_EP_DIRECTION_OUT(X) ((X) & ~HAL_USB_EP_DIRECTION)

// =============================================================================
// HAL_USB_IS_EP_DIRECTION_IN
// -----------------------------------------------------------------------------
/// This macro define if the direction is IN
// =============================================================================
#define HAL_USB_IS_EP_DIRECTION_IN(X) ((X)&HAL_USB_EP_DIRECTION)

// =============================================================================
// HAL_USB_EP_NUM
// -----------------------------------------------------------------------------
/// This macro return the endpoint index
// =============================================================================
#define HAL_USB_EP_NUM(X) ((X) & (~HAL_USB_EP_DIRECTION))

// =============================================================================
// HAL_USB_MPS_T
// -----------------------------------------------------------------------------
/// Mas Packet Size
// =============================================================================
#define HAL_USB_MPS 64

// =============================================================================
// TYPES
// =============================================================================

#define USB_UCBSS_INTERNAL __attribute__((aligned(4), section(".ucbss")))

// =============================================================================
// HAL_USB_CALLBACK_EP_TYPE_T
// -----------------------------------------------------------------------------
/// Type of callback
// =============================================================================
typedef enum {
    /// Event send when a command is receive
    HAL_USB_CALLBACK_TYPE_CMD,
    /// Event send when a data command transfert is finish
    HAL_USB_CALLBACK_TYPE_DATA_CMD,
    /// Event send when a receive transfert is finish
    HAL_USB_CALLBACK_TYPE_RECEIVE_END,
    /// Event send when a transmit transfert is finish
    HAL_USB_CALLBACK_TYPE_TRANSMIT_END,
    /// Event send when interface is enable
    HAL_USB_CALLBACK_TYPE_ENABLE,
    /// Event send when interface is disable
    HAL_USB_CALLBACK_TYPE_DISABLE
} HAL_USB_CALLBACK_EP_TYPE_T;

// =============================================================================
// HAL_USB_SETUP_REQUEST_DESC_T
// -----------------------------------------------------------------------------
/// Description of request
// =============================================================================
typedef struct
{
    uint8_t requestDest : 5;
    uint8_t requestType : 2;
    uint8_t requestDirection : 1;
} HAL_USB_SETUP_REQUEST_DESC_T;

// =============================================================================
// HAL_USB_SETUP_T
// -----------------------------------------------------------------------------
/// Description of USB command
// =============================================================================

typedef struct
{
    HAL_USB_SETUP_REQUEST_DESC_T requestDesc;
    uint8_t request;
    uint16_t value;
    uint16_t index;
    uint16_t lenght;
} PACKED HAL_USB_SETUP_T;

// =============================================================================
// HAL_USB_CALLBACK_RETURN_T
// -----------------------------------------------------------------------------
/// Return value of callback
// =============================================================================
typedef enum {
    HAL_USB_CALLBACK_RETURN_OK,
    HAL_USB_CALLBACK_RETURN_RUNNING,
    HAL_USB_CALLBACK_RETURN_KO
} HAL_USB_CALLBACK_RETURN_T;

// =============================================================================
// HAL_USB_CALLBACK_T
// -----------------------------------------------------------------------------
/// Type use to define endpoint/interface callback. It's call when an endpoint
/// commande  are receive on EP0.
/// @param type kind of action
/// @param setup Setup is the USB command data
// =============================================================================
typedef HAL_USB_CALLBACK_RETURN_T (*HAL_USB_CALLBACK_T)(HAL_USB_CALLBACK_EP_TYPE_T type,
                                                        HAL_USB_SETUP_T *setup);

typedef uint32_t (*HAL_USB_CS_CONSTRUCTOR_T)(uint8_t *buffer);

#include "hal_usb_descriptor_types.h"

// =============================================================================
// HAL_USB_GETDESCRIPTOR_CALLBACK_T
// -----------------------------------------------------------------------------
/// This function is call when USB must send a device descriptor request
/// @return Return a device descriptor
// =============================================================================
typedef HAL_USB_DEVICE_DESCRIPTOR_T *(*HAL_USB_GETDESCRIPTOR_CALLBACK_T)(bool);

// =============================================================================
// GLOBAL VARIABLES
// =============================================================================

// =============================================================================
// FUNCTIONS
// =============================================================================

// =============================================================================
// hal_UsbEpStall
// -----------------------------------------------------------------------------
/// Stall an End point
/// @param ep Define the endpoint index for the direction
/// use #HAL_USB_EP_DIRECTION_IN and use #HAL_USB_EP_DIRECTION_OUT
/// @param stall \c true Set EndPoint Stall
///              \c false Clear EndPoint Stall
// =============================================================================
extern void hal_UsbEpStall(uint8_t ep, bool stall);

// =============================================================================
// hal_UsbOpen
// -----------------------------------------------------------------------------
/// This function enable USB
///
/// This function requests a resource of #HAL_SYS_FREQ_39M.
///
/// @param callback See #HAL_USB_GETDESCRIPTOR_CALLBACK_T
// =============================================================================
extern void hal_UsbOpen(HAL_USB_GETDESCRIPTOR_CALLBACK_T callback);

// =============================================================================
// hal_UsbClose
// -----------------------------------------------------------------------------
/// This function disable USB
// =============================================================================
extern void hal_UsbClose(void);

// =============================================================================
// hal_UsbSend
// -----------------------------------------------------------------------------
/// Send an usb packet
/// @param ep Define the endpoint index for the direction
/// use #HAL_USB_EP_DIRECTION_IN and use #HAL_USB_EP_DIRECTION_OUT
/// @param buffer Pointer on the date buffer to be send.
/// @param size Number of bytes to be send.
/// @param flag For partial send set the flag to 1
/// @return Number of sent bytes or -1 if error
// =============================================================================
extern int hal_UsbSend(uint8_t ep, uint8_t *buffer, uint16_t size, uint32_t flag);

// =============================================================================
// hal_UsbRecv
// -----------------------------------------------------------------------------
/// Recv an usb packet
/// @param ep Define the endpoint index for the direction
/// use #HAL_USB_EP_DIRECTION_IN and use #HAL_USB_EP_DIRECTION_OUT
/// @param buffer Pointer on the data buffer to be send.
/// @param size Number of bytes to be send.
/// @param flag No flag you must set this parameter to zero
/// @return Number of sent bytes or -1 if error
// =============================================================================
extern int hal_UsbRecv(uint8_t ep, uint8_t *buffer, uint16_t size, uint32_t flag);

// =============================================================================
// hal_UsbEnableInterrupt
// -----------------------------------------------------------------------------
/// Enable or disable interrupt for an specific EndPoint. The default value
/// after initialisation is true
/// @param ep Number of Endpoint
/// @param enable \c true Enable the interrupt
///               \c false Disable the interrupt
// =============================================================================
extern void hal_UsbEpEnableInterrupt(uint8_t ep, bool enable);

// =============================================================================
// hal_UsbEpRxTransferedSize
// -----------------------------------------------------------------------------
/// This function return number of bytes send on the last transfert
/// @param ep Number of Endpoint
/// @return Size transfered
// =============================================================================
extern uint16_t hal_UsbEpRxTransferedSize(uint8_t ep);

// =============================================================================
// hal_UsbEpTransfertDone
// -----------------------------------------------------------------------------
/// This function indicate if an transfert is finish.
/// @param ep Number of Endpoint
/// @return return the end transfert status
// =============================================================================
extern bool hal_UsbEpTransfertDone(uint8_t ep);

// =============================================================================
// hal_UsbGetControlFlag
// -----------------------------------------------------------------------------
// =============================================================================
extern bool hal_UsbGetControlFlag(VOID);

// =============================================================================
// hal_UsbReset
// -----------------------------------------------------------------------------
/// This function is use to reset USB and/or change configuration of usb
/// For reset you must do hal_UsbReset(true); sleep 0.5s; hal_UsbReset(false);
/// @param reset If is true, the function is clear usb and power down usb else
/// the function power up usb
// =============================================================================
extern VOID hal_UsbReset(bool reset);

///  @} <- End of USB group

#endif // _HAL_USB_H_
