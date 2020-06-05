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

#ifndef _HAL_SYS_IFC_H_
#define _HAL_SYS_IFC_H_

#include "chip_id.h"
#include "sys_ifc.h"

#include <stdint.h>
#include <stdbool.h>

#define HAL_UNKNOWN_CHANNEL 0xff

/// IFC transaction type Id
typedef enum {
#ifdef CHIP_DIE_8955
    /// Sending data to the sim
    HAL_IFC_SCI_TX = 0,
    /// Receiving data from the sim
    HAL_IFC_SCI_RX = 0x1,
    /// Sending data on the SPI
    HAL_IFC_SPI_TX = 0x2,
    /// Receiving data from the SPI
    HAL_IFC_SPI_RX = 0x3,
    /// Sending data on the SPI
    HAL_IFC_SPI2_TX = 0x4,
    /// Receiving data from the SPI
    HAL_IFC_SPI2_RX = 0x5,
    /// Sending data on the SPI
    HAL_IFC_SPI3_TX = 0x6,
    /// Receiving data from the SPI
    HAL_IFC_SPI3_RX = 0x7,
    /// Sending data on the debug uart
    HAL_IFC_DEBUG_UART_TX = 0x8,
    /// Receiving data from the debug uart
    HAL_IFC_DEBUG_UART_RX = 0x9,
    /// Sending data on the uart 1
    HAL_IFC_UART1_TX = 0xA,
    /// Receiving data from uart 1
    HAL_IFC_UART1_RX = 0xB,
    /// Sending data on the uart 2
    HAL_IFC_UART2_TX = 0xC,
    /// Receiving data from uart 2
    HAL_IFC_UART2_RX = 0xD,
    /// Sending data on the SDMMC
    HAL_IFC_SDMMC_TX = 0xE,
    /// Receiving data from the SDMMC
    HAL_IFC_SDMMC_RX = 0xF,
    /// Sending data on the CAMERA: Doesn't exist
    HAL_IFC_CAMERA_TX_RESERVED = 0x10,
    /// Receiving data from the CAMERA
    HAL_IFC_CAMERA_RX = 0x11,
#if (CHIP_HAS_SDIO == 1)
    /// Sending data on the SDMMC2
    HAL_IFC_SDMMC2_TX = 0x12,
    /// Receiving data from the SDMMC2
    HAL_IFC_SDMMC2_RX = 0x13,
#endif // CHIP_HAS_SDIO == 1
#endif // CHIP_DIE_8955

#ifdef CHIP_DIE_8909
    /// Sending data to the sim
    HAL_IFC_SCI_TX = 0,
    /// Receiving data from the sim
    HAL_IFC_SCI_RX = 0x1,
    /// Sending data to the sim2
    HAL_IFC_SCI2_TX = 0x2,
    /// Receiving data from the sim2
    HAL_IFC_SCI2_RX = 0x3,
    /// Sending data on the SPI
    HAL_IFC_SPI_TX = 0x4,
    /// Receiving data from the SPI
    HAL_IFC_SPI_RX = 0x5,
    /// Sending data on the SPI
    HAL_IFC_SPI2_TX = 0x6,
    /// Receiving data from the SPI
    HAL_IFC_SPI2_RX = 0x7,
    /// Sending data on the SPI
    HAL_IFC_SPI3_TX = 0x8,
    /// Receiving data from the SPI
    HAL_IFC_SPI3_RX = 0x9,
    /// Sending data on the debug uart
    HAL_IFC_DEBUG_UART_TX = 0xA,
    /// Receiving data from the debug uart
    HAL_IFC_DEBUG_UART_RX = 0xB,
    /// Sending data on the uart 1
    HAL_IFC_UART1_TX = 0xC,
    /// Receiving data from uart 1
    HAL_IFC_UART1_RX = 0xD,
    /// Sending data on the uart 2
    HAL_IFC_UART2_TX = 0xE,
    /// Receiving data from uart 2
    HAL_IFC_UART2_RX = 0xF,
    /// Sending data on the uart 3
    HAL_IFC_UART3_TX = 0x10,
    /// Receiving data from uart 3
    HAL_IFC_UART3_RX = 0x11,
    /// Sending data on the uart 4
    HAL_IFC_UART4_TX = 0x12,
    /// Receiving data from uart 4
    HAL_IFC_UART4_RX = 0x13,
    /// Sending data on the SDMMC
    HAL_IFC_SDMMC_TX = 0x14,
    /// Receiving data from the SDMMC
    HAL_IFC_SDMMC_RX = 0x15,
    /// Sending data on the SDMMC2
    HAL_IFC_SDMMC2_TX = 0x16,
    /// Receiving data from the SDMMC2
    HAL_IFC_SDMMC2_RX = 0x17,
    /// Sending data on the CAMERA: Doesn't exist
    HAL_IFC_CAMERA_TX_RESERVED = 0x18,
    /// Receiving data from the CAMERA
    HAL_IFC_CAMERA_RX = 0x19,
#endif // CHIP_DIE_8909

#ifdef CHIP_DIE_8809
	/// Sending data to the sim
		HAL_IFC_SCI_TX,
	/// Receiving data from the sim
		HAL_IFC_SCI_RX,
	/// Sending data on the SPI
		HAL_IFC_SPI_TX,
	/// Receiving data from the SPI
		HAL_IFC_SPI_RX,
	/// Sending data on the SPI
		HAL_IFC_SPI2_TX,
	/// Receiving data from the SPI
		HAL_IFC_SPI2_RX,
	/// Sending data on the SPI
		HAL_IFC_SPI3_TX,
	/// Receiving data from the SPI
		HAL_IFC_SPI3_RX,
	/// Sending data on the debug uart
		HAL_IFC_DEBUG_UART_TX,
	/// Receiving data from the debug uart
		HAL_IFC_DEBUG_UART_RX,
	/// Sending data on the uart 1
		HAL_IFC_UART1_TX,
	/// Receiving data from uart 1
		HAL_IFC_UART1_RX,
	/// Sending data on the uart 2
		HAL_IFC_UART2_TX,
	/// Receiving data from uart 2
		HAL_IFC_UART2_RX,
	/// Sending data on the SDMMC
		HAL_IFC_SDMMC_TX,
	/// Receiving data from the SDMMC
		HAL_IFC_SDMMC_RX,
	/// Sending data on the CAMERA: Doesn't exist
		HAL_IFC_CAMERA_TX_RESERVED,
	/// Receiving data from the CAMERA
		HAL_IFC_CAMERA_RX,
#if (CHIP_HAS_SDIO == 1)
	/// Sending data on the SDMMC //  HAL_IFC_SDMMC2_TX =54,
		HAL_IFC_SDMMC2_TX ,
	/// Receiving data from the SDMMC
		HAL_IFC_SDMMC2_RX , // HAL_IFC_SDMMC2_RX =55,
#endif	
#endif // 
    /// No transaction requested
    HAL_IFC_NO_REQWEST
} HAL_IFC_REQUEST_ID_T;

// =============================================================================
// HAL_IFC_MODE_T
// -----------------------------------------------------------------------------
/// Define the mode used to configure an IFC transfer. This enum describes
/// the width (8, 16 or 32 bits) and if the transfer is autodisabled or manually
/// disabled.
// =============================================================================
typedef enum {
    HAL_IFC_SIZE_8_MODE_MANUAL = (0 | 0),
    HAL_IFC_SIZE_8_MODE_AUTO = (0 | SYS_IFC_AUTODISABLE),
#if (CHIP_HAS_SYS_IFC_SIZE == 2)
    HAL_IFC_SIZE_16_MODE_MANUAL = (SYS_IFC_SIZE_HALF_WORD | 0),
    HAL_IFC_SIZE_16_MODE_AUTO = (SYS_IFC_SIZE_HALF_WORD | SYS_IFC_AUTODISABLE),
    HAL_IFC_SIZE_32_MODE_MANUAL = (SYS_IFC_SIZE_WORD | 0),
    HAL_IFC_SIZE_32_MODE_AUTO = (SYS_IFC_SIZE_WORD | SYS_IFC_AUTODISABLE),
#elif (CHIP_HAS_SYS_IFC_SIZE == 1)
    HAL_IFC_SIZE_32_MODE_MANUAL = (SYS_IFC_SIZE | 0),
    HAL_IFC_SIZE_32_MODE_AUTO = (SYS_IFC_SIZE | SYS_IFC_AUTODISABLE),
#endif
} HAL_IFC_MODE_T;

// =============================================================================
// hal_IfcGetOwner
// -----------------------------------------------------------------------------
/// Get the owner ID of an IFC channel (i.e. the module using the channel).
/// @param channel number to check
/// @return The owner number associated with the channel
// =============================================================================
HAL_IFC_REQUEST_ID_T __attribute__((deprecated)) hal_IfcGetOwner(uint8_t channel);

// =============================================================================
// hal_IfcChannelRelease
// -----------------------------------------------------------------------------
/// Force the release of a channel owned by a request.
///
/// The channel is only released if the specified request
/// owns the channel.
///
/// @param requestId Describe the direction of the tranfer (rx or
/// tx) and the module to or from which data are to be moved.
/// @param channel Channel to release
// =============================================================================
void hal_IfcChannelRelease(HAL_IFC_REQUEST_ID_T requestId, uint8_t channel);

// =============================================================================
// hal_IfcChannelFlush
// -----------------------------------------------------------------------------
/// Empty the FIFO a specified channel.
///
/// If #requestId does not match #channel owner, does not do anything.
///
/// @param requestId Describe the direction of the tranfer (rx or
/// tx) and the module to or from which data are to be moved.
/// @param channel Channel whose FIFO is to be clear.
// =============================================================================
void hal_IfcChannelFlush(HAL_IFC_REQUEST_ID_T requestId, uint8_t channel);

// =============================================================================
// hal_IfcChannelIsFifoEmpty
// -----------------------------------------------------------------------------
/// Returns \c TRUE when the FIFO is empty.
///
/// If #requestId does not match #channel owner, returns TRUE.
///
/// @param requestId Describe the direction of the tranfer (rx or
/// tx) and the module to or from which data are to be moved.
/// @param channel Channel whose FIFO is to be checked.
// =============================================================================
bool hal_IfcChannelIsFifoEmpty(HAL_IFC_REQUEST_ID_T requestId, uint8_t channel);

// =============================================================================
// hal_IfcTransferStart
// -----------------------------------------------------------------------------
/// Start an IFC transfer
///
/// This is a non blocking function that starts the transfer
/// and returns the hand.
///
/// @param requestId Describe the direction of the tranfer (rx or
/// tx) and the module to or from which data are to be moved.
/// @param memStartAddr. Start address of the buffer where data
/// to be sent are located or where to put the data read, according
/// to the request defined by the previous parameter
/// @param xferSize Number of bytes to transfer. The maximum size
/// is 2^20 - 1 bytes.
/// @param ifcMode Mode of the transfer (Autodisable or not, 8 or 32 bits)
/// @return Channel got or HAL_UNKNOWN_CHANNEL.
// =============================================================================
uint8_t hal_IfcTransferStart(HAL_IFC_REQUEST_ID_T requestId, uint8_t *memStartAddr, uint32_t xferSize, HAL_IFC_MODE_T ifcMode);

// =============================================================================
// hal_IfcGetTc
// -----------------------------------------------------------------------------
/// Returns the transfer count of the IFC.
/// If #requestId does not match #channel owner, returns 0.
///
/// @param requestId Describe the direction of the tranfer (rx or
/// tx) and the module to or from which data are to be moved.
/// @param channel Number of the channel whose transfer we are concerned for.
/// @return The number of bytes remaining to be transfered.
// =============================================================================
uint32_t hal_IfcGetTc(HAL_IFC_REQUEST_ID_T requestId, uint8_t channel);

// =============================================================================
// hal_IfcExtendTransfer
// -----------------------------------------------------------------------------
/// Extend the transfer size of the channel of
/// the number ox bytes passed as a parameter.
///
/// Should be used only when a channel has been locked.
///
/// @param xferSize Number of bytes to add to the
/// transfer size of this channel
// =============================================================================
void hal_IfcExtendTransfer(uint8_t channel, uint16_t xferSize);

// =============================================================================
// hal_IfcGetChannel
// -----------------------------------------------------------------------------
/// Get an IFC channel opend in NO auto-disable mode
///
/// @param requestId Describe the direction of the tranfer (rx or
/// tx) and the module to or from which data are to be moved.
/// @param ifcMode Mode of the transfer (Autodisable or not, 8 or 32 bits)
/// @return The channel number got or HAL_UNKNOWN_CHANNEL
// =============================================================================
uint8_t hal_IfcGetChannel(HAL_IFC_REQUEST_ID_T requestId, HAL_IFC_MODE_T ifcMode);

// =============================================================================
// hal_IfcSetStartAddress
// -----------------------------------------------------------------------------
/// Set the start address of a previously opened (with hal_IfcGetChannel)
/// IFC channel.
///
/// Should be used only when a channel has been locked.
///
/// @param channel Opened channel whose start address will be set.
/// @param startAddress Set start address of the channel.
// =============================================================================
void hal_IfcSetStartAddress(uint8_t channel, const uint8_t *startAddress);

// =============================================================================
// hal_IfcClearFlush
// -----------------------------------------------------------------------------
/// Clear ifc hardware FLUSH bit, so that it can continue running.
///
/// @param requestId Describe the direction of the tranfer (rx or
/// tx) and the module to or from which data are to be moved.
/// @param channel Number of the channel whose transfer we are concerned for.
// =============================================================================
void hal_IfcClearFlush(HAL_IFC_REQUEST_ID_T requestId, uint8_t channel);

// =============================================================================
// hal_IfcChannelIsRunning
// -----------------------------------------------------------------------------
/// Check if a specific ifc channel is still running.
///
/// @param requestId Describe the direction of the tranfer (rx or
/// tx) and the module to or from which data are to be moved.
/// @param channel Number of the channel whose transfer we are concerned for.
/// @return The channel is still running
// =============================================================================
bool hal_IfcChannelIsRunning(HAL_IFC_REQUEST_ID_T requestId, uint8_t channel);

#endif //  HAL_SYS_IFC_H
