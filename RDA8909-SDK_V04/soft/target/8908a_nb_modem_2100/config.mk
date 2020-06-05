#
# Automatically generated file; DO NOT EDIT.
# RDA Feature Phone Configuration
#

#
# --- RDA Software Configuration ---
#

#
# Platform
#

#
# boot
#

#
# --- platform/boot ---
#
FOTA_SUPPORT	:=y

#
# chip
#

#
# --- platform/chip ---
#
CT_ASIC	:=8909
8955	:=n
8809	:=n
CT_CHIP_DIE	:=8909
null	:=n
gcc4_xcpu	:=n
CT_COMPILER	:=gcc7_xcpu2
fpga	:=n
CT_ASIC_CFG	:=chip
CHIP_METAL_ID	:=U02
CRYSTAL_WITHOUT_OSCILLATOR	:=y
SMTRF_2G_DBG	:=n

#
# drivers
#

#
# --- platform/edrv ---
#

#
# ATV
#

#
# audio
#

#
# --- platform/edrv/aud ---
#

#
# tv
#

#
# --- platform/edrv/aud/tv ---
#
AD_MODEL	:=codec_gallite
MIC_CAPLESS_MODE	:=y

#
# bluetooth
#

#
# --- platform/edrv/btd ---
#

#
# usb
#
UCTLS_SERVICE	:=y
_UTRACE_	:=y
_UMSS_	:=y
_UCDCACM_	:=y
_UVIDEO_	:=n
_URNDIS_	:=n
_UMSS_DUAL_MC_	:=n

#
# camera
#

#
# --- platform/edrv/camd ---
#
CAMERA_MODEL	:=
MJPG_SUPPORT	:=y
CAMERA_IF	:=spi

#
# fm
#

#
# --- platform/edrv/fmd ---
#
FM_MODEL	:=rdafm_8909
FM_USING_I2S	:=n
FM_USE_32K_CLK_PIN	:=0

#
# lcd
#

#
# --- platform/edrv/lcdd ---
#
LCD_MODEL	:=nv3029e
LCD_IF	:=gouda
USE_SPI_LCD	:=y
__USE_LCD_FMARK__	:=n
LCD_BACKLIGHT_CHARGE_PUMP	:=n

#
# mem
#

#
# --- platform/edrv/memd ---
#
FLSH_MODEL	:=flsh_spi32m
FLSH_IF	:=spi
RAM_SIZE_FLAG	:=__32Mbit__
SYS_MEMD_EBC_CLK	:=__156MHz__
SYS_MEMD_FLSH_SPI_CLK	:=__78MHz__
SYS_MMI_CLK	:=__104MHz__
RAM_INIT_CLOCK_RATE	:=144000000

#
# FLASH layout
#
FLASH_SIZE	:=0x400000
FLASH_BOOT_OFFSET	:=0x10000
FOTA_BACKUP_AREA_START	:=0x380000
FOTA_BACKUP_AREA_SIZE	:=0x10000
USE_LEGACY_SPIFFS	:=n
SPIFFS_FLASH_START	:=0x390000
SPIFFS_FLASH_SIZE	:=0x68000
SFFS_FLASH_EB_SIZE	:=0x8000
SFFS_FLASH_PB_SIZE	:=0x200
USER_DATA_BASE	:=0x3F8000
USER_DATA_SIZE	:=0x0
USER_DATA_FLASH_EB_SIZE	:=0x1000
USER_DATA_FLASH_PB_SIZE	:=0x200
CALIB_BASE	:=0x3F8000
CALIB_RF2G_BASE	:=0x3FA000
CALIB_RFNB_BASE	:=0x3FC000
CALIB_SIZE	:=0x6000
FACT_SETTINGS_BASE	:=0x3FE000
FACT_SETTINGS_SIZE	:=0x2000

#
# pm
#

#
# --- platform/edrv/pmd ---
#
PM_MODEL	:=pmu_8909
AUD_SPK_LINE_L_R_DOUBLE	:=y
class_ab	:=n
AUD_SPK_LINE_CLASS_MODE	:=class_d
class_k	:=n

#
# rf
#

#
# --- platform/edrv/rfd ---
#
PA_MODEL	:=pasw_rda6625
pasw_rda6231	:=n
pasw_hs8292u	:=n
XCV_MODEL	:=xcv_8909
XCV_TS_ENABLE	:=y
PA_VRAMP_220PF	:=y
USE_EXT_XTAL_32K	:=n
XCV_8909_GPIO	:=n
XCV_RDA8909NEZ	:=y

#
# sim
#
DUALSIM_MODEL	:=rda1203_gallite_CT1129
USIM_SUPPORT	:=y
NUMBER_OF_SIM	:=2
USER_SIM_ORDER	:=1 2

#
# Touch Screen
#
TSD_MODEL	:=

#
# gpio extend
#
GPIOI2C_MODEL	:=n
GPIOSPI_MODEL	:=n

#
# mcd
#
MCD_IF	:=sdmmc

#
# gpsd
#

#
# --- platform/edrv/gpsd ---
#
GPSD_MODEL	:=
GPS_DEFAULT_UART	:=0
GPS_SUPPORT	:=n

#
# wcn
#

#
# service
#

#
# --- platform/service ---
#

#
# base
#

#
# --- platform/service/base ---
#
CFG_NEW_MECHANISM_TEST	:=n
REDUNDANT_DATA_REGION	:=n

#
# gprs
#
EGPRS_SUPPORT	:=n
GPRS_SUPPORT	:=y

#
# Net Support
#

#
# --- platform/service/net/ ---
#
CFW_TCPIP_SUPPORT	:=y
CFW_PPP_SUPPORT	:=y
MUPNP_USE_OPENSSL	:=y
WITH_MBEDDTLS	:=y
LIBHTTP_SUPPORT	:=y
LIBCOAP_SUPPORT	:=y
LIBLWM2M_SUPPORT	:=y
LIBEDP_SUPPORT	:=y
MBEDTLS_SUPPORT	:=y
LIBXML_SUPPORT	:=y
LIBJSON_SUPPORT	:=y
LIBALIOTX_SUPPORT	:=y
CMCC_CISSDK_SUPPORT	:=y
LWIP_SUPPORT	:=y
LWIP_DEBUG_ON	:=y
LWIP_PPP_ON	:=y
LWIP_IPV4_ON	:=y
LWIP_IPV6_ON	:=y
AWORKER_SUPPORT	:=y
CALL_AMR_SUPPORT	:=y

#
# system
#

#
# --- platform/system ---
#

#
# stack
#

#
# --- platform/system/stack ---
#
LTE_NBIOT_SUPPORT	:=y
FPGA_NBCPU	:=y
BUILD_BCPU_PSRAM	:=y
NO_BCPU_IMAGE	:=n

#
# calib
#

#
# --- platform/system/calib ---
#
CES_DISPLAY	:=n

#
# mdi
#

#
# --- platform/system/mdi ---
#
MEDIA_RM_SUPPORT	:=n
VIDEO_PLAYER_SUPPORT	:=n
SOUND_RECORDER_SUPPORT	:=n
VIDEO_RECORDER_SUPPORT	:=n
MEDIA_MIDI_SUPPORT	:=n

#
# Custom Setup
#
CT_PROTOSTACK_IN_RAM	:=y
HW_BOARD_TYPE	:=YUGA_2100
EXPORT_BOARD_INFO	:=y
EXPORT_BOARD_FLAGS	:=PM_MODEL FM_MODEL

#
# Lower Power Options
#

#
# Application
#

#
# --- Application ---
#

#
# Communication
#

#
# --- application/communication ---
#

#
# Features
#

#
# Call
#

#
# --- application/coolmmi/mmi/calls ---
#

#
# --- application/coolmmi/mmi/callmanagement ---
#

#
# Messages
#

#
# --- application/coolmmi/mmi/messages ---
#
PHONE_SMS_ENTRY_COUNT	:=100
SIM_SMS_ENTRY_COUNT	:=255
CM_SMS_MAX_MSG_NUM	:=100
MAX_INDEX_MAP_LENGTH	:=100
CB_SUPPORT	:=n

#
# Phonebook
#

#
# --- application/coolmmi/mmi/phonebook ---
#
PHONE_PHB_ENTRY_COUNT	:=100
MAX_PHB_PHONE_ENTRY	:=100

#
# Profiles & Settings
#

#
# --- application/coolmmi/mmi/profiles ---
#

#
# --- application/coolmmi/mmi/setting ---
#

#
# ---FM Record Codec---
#

#
# Idlescreen
#

#
# --- application/coolmmi/mmi/idlescreen ---
#

#
# Watch
#

#
# --- Watch Options ---
#

#
# Multimedia
#

#
# Radio
#

#
# Audio
#

#
# --- application/coolmmi/mmi_csdapp/audioplayer ---
#
MULTI_MEDIA_AMR_SUPPORT	:=y
MMI_SUPPORT_MAGIC_SOUND	:=n

#
# Video
#
MEDIA_H264_SUPPORT	:=n
MEDIA_VOCVID_SUPPORT	:=y

#
# Camera
#

#
# --- application/coolmmi/mmi_csdapp/camera ---
#
CAM_MD_SUPPORT	:=n

#
# SoundRecorder
#

#
# --- application/coolmmi/mmi/soundrecorder ---
#

#
# ATV
#

#
# --- application/coolmmi/mmi_csdapp/analogtv ---
#
ANALOG_TV_SUPPORT	:=n

#
# FileManagement
#

#
# --- application/coolmmi/mmi_csdapp/filemgr ---
#

#
# Wap & MMS
#

#
# --- GPRS Options ---
#

#
# Bluetooth
#

#
# --- application/coolmmi/mmi/bluetooth ---
#

#
# USB
#

#
# --- application/coolmmi/mmi/usb ---
#

#
# Organizer
#

#
# --- application/coolmmi/mmi/organizer ---
#

#
# EngineerMode
#

#
# --- application/coolmmi/mmi_csdapp/engineermode ---
#

#
# Resource
#

#
# --- application/target_res ---
#

#
# Language
#

#
# --- languages support ---
#

#
# Inputmethod
#

#
# --- Inputmethod ---
#

#
# Fonts
#

#
# --- Fonts and Others---
#
CT_ERES	:=qqvga_3232
qvga_3264	:=n
qcif_3264	:=n
128_128	:=n
160_128_3216	:=n
220_176_3232	:=n
320_240_6432	:=n
240_240	:=n
TARGET_MEM_ULC_3216	:=y
CT_CUSTSECTOR	:=n

#
# Compress
#

#
# --- Compress Options ---
#
CT_COMPRESS_CODE_SECTION	:=n
CT_COMPRESS_PREMAIN	:=n

#
# Display
#

#
# SIM
#

#
# --- SIM Options ---
#
MMI_SUPPORT_SENDKEY2	:=n

#
# diag && BBAT
#

#
# --- application/diag ---
#
SUPPORT_SPRD_BBAT	:=n

#
# Device
#

#
# NvRam
#

#
# --- application/adaptation ---
#
USE_SPIFFS_NVRAM	:=n

#
# Sensor
#
MMI_SUPPORT_GSENSOR	:=n

#
# Key
#

#
# Default Setup
#

#
# --- Default Options ---
#

#
# AT
#
CT_MODEM	:=1
AT_DEFAULT_UART	:=2
AT_UART_LPS_SUPPORT	:=y
AT_SECOND_UART_SUPPORT	:=n
_USE_AT_OC_GPIO_	:=2
AT_USB_MODEM_NO_MMMI	:=y
AT_CMUX_SUPPORT	:=y
AT_DT_ONLY	:=y
GCF_TTS_MODEL	:=n
AT_HTTP_SUPPORT	:=y
AT_COAP_SUPPORT	:=y
AT_CTCC_DATAREG	:=y
AT_CUCC_DATAREG	:=y
AT_CISSDK_MIPL_SUPPORT	:=y
AT_OCEANCONNECT_SUPPORT	:=y
AT_DM_LWM2M_SUPPORT	:=y
AT_CMIOT_TCPIP_SUPPORT	:=n
AT_CMIOT_FTP_SUPPORT	:=n
AT_CMIOT_CIOT_SUPPORT	:=y
AT_CMIOT_HTTP_SUPPORT	:=y
LWIP_TEST	:=n
AT_FOTA_SUPPORT	:=y
DEFAULT_SIM_SLOT	:=0
AT_MQTTSN_SUPPORT	:=n
AT_FILESYSTEM_SUPPORT	:=y
AT_QTCPIP_SUPPORT	:=n

#
# Debug
#

#
# --- Debug Options ---
#
WITHOUT_WERROR	:=y

#
# --- Register Debug Options ---
#
SPI_REG_DEBUG	:=y
I2C_REG_DEBUG	:=n

#
# --- Profile Options ---
#

#
# --- Trace Options ---
#
AT_NO_TRACE	:=n
MMI_NO_TRACE	:=y
WAP_NO_TRACE	:=y
CSW_NO_TRACE	:=n
MCI_NO_TRACE	:=y
STACK_NO_PRINTF	:=n
HAL_NO_PRINTF	:=y
PAL_NO_TRACE	:=y
VOIS_NO_PRINTF	:=y
EDRV_NO_TRACE	:=y
CALIB_NO_PRINTF	:=y
LWIP_NO_TRACE	:=n
HTTP_NO_TRACE	:=y
COAP_NO_TRACE	:=y
LWM2M_NO_TRACE	:=y
ALIMQTT_NO_TRACE	:=y
MBEDTLS_NO_TRACE	:=y

#
# Default
#
CT_ROMULATOR	:=n
USE_KCONFIG	:=y
