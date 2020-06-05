/*
 *
 * Automatically generated file; DO NOT EDIT.
 * RDA Feature Phone Configuration
 *
 */

#ifndef __FP_CONFIG_H__
#define __FP_CONFIG_H__

/* --- RDA Software Configuration --- */

/* Platform */

/* boot */

/* --- platform/boot --- */
#define FOTA_SUPPORT

/* chip */

/* --- platform/chip --- */
#define MCU_PLL_FREQ_288M
#define SIM_RX_IFC_IN_SRAM
#define SIM_TX_IFC_IN_SRAM
#define CRYSTAL_WITHOUT_OSCILLATOR

/* drivers */

/* --- platform/edrv --- */

/* ATV */

/* audio */

/* --- platform/edrv/aud --- */

/* tv */

/* --- platform/edrv/aud/tv --- */
#define RECV_USE_SPK_LINE
#define PM_EARPIECE_DET_DEBOUNCE
#define MODULE_EAR_DETECT
#define AUD_2_IN_1_SPK
#define VOLUME_WITH_15_LEVEL
#define VOIS_DUMP_PCM

/* bluetooth */

/* --- platform/edrv/btd --- */

/* usb */
#define _UTRACE_
#define _UMSS_
#define _UCDCACM_
#define __MMI_USB_COM_PORT__

/* camera */

/* --- platform/edrv/camd --- */
#define CAMERA_MODULE
#define CAMERA_SUPPORT
#define APPMEM_SUPPORT
#define MJPG_SUPPORT
#define CAMERA_SUPPORT_300K_PIXELS
#define __CAMERA_FEATURE_FLASH__
#define _CAM_SMALL_MEM_

/* fm */

/* --- platform/edrv/fmd --- */
#define FM_LDO_WORKAROUND

/* lcd */

/* --- platform/edrv/lcdd --- */
#define USE_SPI_LCD
#define lcd_line_8_low

/* mem */

/* --- platform/edrv/memd --- */
#define __PRJ_WITH_SPIFLSH__
#define FLASH_WP_ENABLE
#define FLASH_DEFAULT_WP_ALL
#define USE_OPIDDR_PSRAM
#define RAM_INIT_CLOCK_RATE 144000000
#define SPI_FLSH_78M
#define MMI_CLK_IS_104M
#define __SPIFLSH_SUPPORT_SOFTRESET__

/* FLASH layout */
#define FLASH_SIZE 0x400000
#define FLASH_BOOT_OFFSET 0x10000
#define FOTA_BACKUP_AREA_START 0x380000
#define FOTA_BACKUP_AREA_SIZE 0x10000
#define SPIFFS_FLASH_START 0x390000
#define SPIFFS_FLASH_SIZE 0x68000
#define SFFS_FLASH_EB_SIZE 0x8000
#define SFFS_FLASH_PB_SIZE 0x200
#define USER_DATA_BASE 0x3F8000
#define USER_DATA_SIZE 0x0
#define USER_DATA_FLASH_EB_SIZE 0x1000
#define USER_DATA_FLASH_PB_SIZE 0x200
#define CALIB_BASE 0x3F8000
#define CALIB_RF2G_BASE 0x3FA000
#define CALIB_RFNB_BASE 0x3FC000
#define CALIB_SIZE 0x6000
#define FACT_SETTINGS_BASE 0x3FE000
#define FACT_SETTINGS_SIZE 0x2000

/* pm */

/* --- platform/edrv/pmd --- */

/* rf */

/* --- platform/edrv/rfd --- */
#define XCV_TS_ENABLE
#define INTERNAL_XCV_CONTROL_PASW
#define __RF_RDAPASW_TWOBAND_AS_FOURBAND__
#define PASW_RDAPA
#define PASW_MODEM
#define TXPOWER_TEMPERATURE_OFFSET
#define XCV_PLL_SDM_MODE
#define MULTI_BANDWIDE
#define USE_BB_DC_CANCEL

/* sim */
#define USER_SIM_SWAP

/* Touch Screen */

/* gpio extend */

/* mcd */

/* gpsd */

/* --- platform/edrv/gpsd --- */
#define GPS_DEFAULT_UART 0

/* wcn */

/* service */

/* --- platform/service --- */

/* base */

/* --- platform/service/base --- */

/* gprs */
#define __MOD_TCM__
#define __GPRS_MODE__
#define __TCPIP__
#define __GPRS_SWITCH__
#define CFW_GPRS_SUPPORT

/* Net Support */

/* --- platform/service/net/ --- */
#define CFW_TCPIP_SUPPORT
#define CFW_PPP_SUPPORT
#define MUPNP_USE_OPENSSL
#define WITH_MBEDDTLS
#define LIBHTTP_SUPPORT
#define LIBCOAP_SUPPORT
#define LIBLWM2M_SUPPORT
#define LIBEDP_SUPPORT
#define MBEDTLS_SUPPORT
#define LIBXML_SUPPORT
#define LIBJSON_SUPPORT
#define LIBALIOTX_SUPPORT
#define CMCC_CISSDK_SUPPORT
#define LWIP_SUPPORT
#define LWIP_DEBUG_ON
#define LWIP_PPP_ON
#define LWIP_IPV4_ON
#define LWIP_IPV6_ON
#define AWORKER_SUPPORT

/* system */

/* --- platform/system --- */

/* stack */

/* --- platform/system/stack --- */
#define LTE_NBIOT_SUPPORT
#define FPGA_NBCPU
#define BUILD_BCPU_PSRAM
#define LTE_SUPPORT
#define STACK_SUPPORT_LTE_FDD
#define STACK_SUPPORT_TDL
#define NB_RAB_TX_MULTI
#define NB_UL_NO_PKT_LOSS
#define F8_HW_ENABLE
#define __TCU_ENABLE__
#define __RFD_RBDP_SWITCH__
#define STARPOINT_TEST
#define SXR_WORK_MODE
#define TRA_TRACE_ENABLE
#define TRA_ENABLE

/* calib */

/* --- platform/system/calib --- */

/* mdi */

/* --- platform/system/mdi --- */
#define DONOT_SUPPORT_DUAL_BUFFER

/* Custom Setup */

/* Lower Power Options */
#define HAL_FORCE_LPS_OS_ALIGN
#define XCV_WAKEUP_FRAME_NB
#define XCV_DAC_MUX_EN_DISABLE
#define __L1_TWO_BURST_PCH__

/* Application */

/* --- Application --- */

/* Communication */

/* --- application/communication --- */
#define __DCS1800__
#define __EGSM900__
#define __GSM850__
#define __PCS1900__

/* Features */

/* Call */

/* --- application/coolmmi/mmi/calls --- */
#define __MMI_CALL_RECORDER__
#define __MMI_AUTO_CALL_RECORDER__
#define __MMI_CALL_RECORDER_FILE_SAVE_PATH__
#define INCOMING_CALL_RINGTONE_AUD_MODE_LOUDSPK_HEADSET

/* --- application/coolmmi/mmi/callmanagement --- */
#define __MMI_CALLING_CALLHISTORY_SUPPORT__

/* Messages */

/* --- application/coolmmi/mmi/messages --- */
#define PHONE_SMS_ENTRY_COUNT 100
#define SIM_SMS_ENTRY_COUNT 255
#define __MMI_MESSAGES_DRAFT_BOX__
#define __MMI_MESSAGES_DELETE_SAME_NUMER__
#define __MMI_MESSAGES_SMS_MARK_SEVERAL__
#define __MMI_MESSAGES_DRAFT_BOX_SPLIT__
#define __MMI_MESSAGES_COPY__
#define SUPPORT_SMS_EXPORT_IMPORT
#define __MMI_MSG_NUM_ADD_TO_BLACKLIST__
#define __MMI_MESSAGES_RENAME_OUTBOX__
#define __MMI_MESSAGES_VOICE_MAIL__
#define __MMI_MESSAGES_MULTI_REPLY__
#define __MMI_MESSAGES_BLACK_LIST__
#define __MMI_MESSAGE_DIFFERENTIATE_STORAGE__
#define __MMI_MESSAGES_PREFER_STORAGE_MEMORY_STATUS__
#define __MMI_MESSAGES_CONCAT_SMS__
#define __MMI_MESSAGES_TEMPLATE__
#define _MUTILANG_TEMPLATE_
#define __MMI_MESSAGES_SEND_BY_GROUP__
#define __MMI_MESSAGES_SEND_TO_MANY__
#define __MMI_MESSAGES_SEND_TO_MANY_BY_LIST__
#define __MMI_MESSAGES_INSERT_FROM_PHB__
#define __MMI_MESSAGES_CONTINUE_SEND_AFTER_FAIL__

/* Phonebook */

/* --- application/coolmmi/mmi/phonebook --- */
#define PHONE_PHB_ENTRY_COUNT 100
#define __MMI_PHB_SLIM_OPTIONAL_FIELD__
#define __PHB_CALLER_IMAGE_SAVE_PATH_ONLY__
#define __MMI_PHB_MARK_SEVERAL__
#define __MMI_PHB_GROUP_MARK_SEVERAL__
#define SUPPORT_PHB_EXPORT_IMPORT

/* Profiles & Settings */

/* --- application/coolmmi/mmi/profiles --- */
#define __MMI_KEYPAD_LIGHT_SETTIMER_SUPPORT__
#define __MMI_USER_DEF_PROFILE__

/* --- application/coolmmi/mmi/setting --- */
#define __MMI_PRIVACY_PROTECTION__
#define __FLIGHT_MODE_SUPPORT__
#define __MMI_SOUND_EFFECT__

/* ---FM Record Codec--- */

/* Idlescreen */

/* --- application/coolmmi/mmi/idlescreen --- */
#define __MMI_DEDICATED_KEY_SHORTCUTS__
#define SHORTCUTS_APP

/* Watch */

/* --- Watch Options --- */

/* Multimedia */

/* Radio */
#define __MMI_FM_RADIO_BIND_EARPHONE__

/* Audio */

/* --- application/coolmmi/mmi_csdapp/audioplayer --- */
#define FMGR_AUDIO_PLAYER_SUPPORT
#define __AUDPLY_SUPPORT_VIDEO_FORMAT__
#define __AUDPLY_SUPPORT_M4A_ONLY_WITH_VIDPLY__

/* Video */
#define MEDIA_VOCVID_SUPPORT

/* Camera */

/* --- application/coolmmi/mmi_csdapp/camera --- */
#define __MMI_CAMERA__
#define __MMI_CAMERA_FEATURE_WATCHDOG_TIMEOUT__
#define __MMI_DISABLE_DUAL_SENSOR__
#define __CAMERA_FEATURE_EFFECT__
#define __CAMERA_FEATURE_EFFECT_NORMAL__
#define __CAMERA_FEATURE_EFFECT_ANTIQUE__
#define __CAMERA_FEATURE_EFFECT_REDRISH__
#define __CAMERA_FEATURE_EFFECT_GREENRISH__
#define __CAMERA_FEATURE_EFFECT_BLUERISH__
#define __CAMERA_FEATURE_EFFECT_BLACKWHITE__
#define __CAMERA_FEATURE_EFFECT_NEGATIVE__
#define __CAMERA_FEATURE_CONTRAST__
#define __CAMERA_FEATURE_AUTO_SAVE__
#define __CAMERA_FEATURE_WB__
#define __CAMERA_FEATURE_CONT_SHOT__
#define __CAMERA_FEATURE_BANDING__
#define CAMERA_SUPPORT_PREVIEW_WITHOUT_TFLASH

/* SoundRecorder */

/* --- application/coolmmi/mmi/soundrecorder --- */
#define __MMI_SOUND_RECORDER__

/* ATV */

/* --- application/coolmmi/mmi_csdapp/analogtv --- */

/* FileManagement */

/* --- application/coolmmi/mmi_csdapp/filemgr --- */
#define FMGR_USING_CACHE
#define __SUPPORT_MEMORY_CARD_RENAME__
#define __MMI_IMAGEVIEWER_MARK_SEVERAL__
#define __MMI_FILEMANAGER_MARK_SEVERAL__
#define __MMI_FILE_MANAGER__

/* Wap & MMS */

/* --- GPRS Options --- */

/* Bluetooth */

/* --- application/coolmmi/mmi/bluetooth --- */

/* USB */

/* --- application/coolmmi/mmi/usb --- */
#define __MMI_USB_SUPPORT__
#define __USB_ENABLE__
#define __MMI_EXT_DEVICE__

/* Organizer */

/* --- application/coolmmi/mmi/organizer --- */
#define CALENDAR_SUPPORT
#define TODOLIST_SUPPORT
#define ORGANIZER_SUPPORT
#define __MOD_FLASHLIGHT__

/* EngineerMode */

/* --- application/coolmmi/mmi_csdapp/engineermode --- */
#define __MMI_ENGINEER_MODE__
#define __MMI_EM_AUDIO_SPEECH_ENHANCEMENT__

/* Resource */

/* --- application/target_res --- */

/* Language */

/* --- languages support --- */
#define __MMI_LANG_ENGLISH__
#define ML_SUPPORT
#define ML_SUPPORT_ISO8859_1

/* Inputmethod */

/* --- Inputmethod --- */
#define __MMI_PREFER_INPUT_METHOD__

/* Fonts */

/* --- Fonts and Others--- */
#define __MMI_CHSET_WESTERN_WIN__
#define FLASH_OPT
#define MMI_ULC
#define MEM_ULC_3216
#define __MMI_RESOURCE_SLIM_ON_128X160__
#define __MMI_RESOURCE_SLIM_AUD_SOURCE__
#define __MMI_FM_SLIM_SKIN__
#define __MMI_SLIM_LISTMENU_NUMBER__
#define SLIM_AUDIO_PROFILE
#define __SLIM_EMS__
#define __MMI_SLIM_PROGRESS_ANIMATION__
#define __MMI_SLIM_CALCULATOR__
#define DAF_DECODE
#define AUDIO_PLAYER_SUPPORT
#define __MMI_MM_SLIM_RESOURCE__
#define __MMI_FOLDER_DETAIL__

/* Compress */

/* --- Compress Options --- */
#define VOCCODE_IN_PSRAM

/* Display */
#define LCDSIZE_128_160
#define __MMI_MAINLCD_128X160__
#define LCD_QVGA_USED_AS_QQVGA
#define __MMI_USING_BLACK_THEME_BG__

/* SIM */

/* --- SIM Options --- */
#define ADP_SIM_NUMBER 2
#define MMI_SIM_NUMBER 2
#define __MMI_MULTI_SIM__
#define __ADP_MULTI_SIM__

/* diag && BBAT */

/* --- application/diag --- */

/* Device */
#define ADP_EARPIECE_DET_DEBOUNCE
#define SUPPORT_EP_WITHOUT_MIC

/* NvRam */

/* --- application/adaptation --- */

/* Sensor */

/* Key */
#define __MMI_NO_SIDEKEY__
#define __NO_SIDE_VOLUME_KEY_STAR_POUND__

/* Default Setup */

/* --- Default Options --- */
#define __EM_MODE__
#define __GSM_MODE__
#define __UCS2_ENCODING
#define __FF_AUDIO_SET__
#define __MCD__
#define __SAT__
#define __VIBRATOR__
#define __MOD_CSM__
#define __MOD_NVRAM__
#define __MOD_ORGANIZER__
#define __MOD_PHB__
#define __MOD_RAC__
#define __MOD_SIM__
#define __MOD_SMS__
#define __MOD_SMSAL__
#define __MOD_SMU__
#define __MOD_UEM__
#define __MED_MMA_MOD__
#define __MMI_IMAGE_VIEWER__
#define __MMI_MERGE_SAT_TO_MAINMENU__
#define VM_SUPPORT
#define SIM_APP_TOOLKIT
#define AAC_DECODE
#define __MMI_RESOURCE_SLIM__
#define JPG_DECODE_USING_SOFTWARE
#define JPG_DECODE
#define PHB_REJECTCALL_NO_RECORD_AND_MENU
#define __MMI_MSG_MEMORY_STATUS_DISPLAY_NUM__

/* AT */
#define AT_DEFAULT_UART 2
#define AT_UART_LPS_SUPPORT
#define AT_MODULE_SUPPORT_SLEEP
#define _USE_AT_OC_GPIO_ 2
#define AT_CMUX_SUPPORT
#define AT_DT_ONLY
#define AT_NITZ_SUPPORT
#define AT_HTTP_SUPPORT
#define AT_PING_SUPPORT
#define AT_NETIF_SUPPORT
#define AT_COAP_SUPPORT
#define AT_CTCC_DATAREG
#define AT_CUCC_DATAREG
#define AT_MQTT_SUPPORT
#define AT_MQTT_ALIOTX_SUPPORT
#define AT_CISSDK_MIPL_SUPPORT
#define AT_OCEANCONNECT_SUPPORT
#define AT_DM_LWM2M_SUPPORT
#define AT_CMIOT_CIOT_SUPPORT
#define AT_CMIOT_HTTP_SUPPORT
#define AT_FOTA_SUPPORT
#define DEFAULT_SIM_SLOT 0
#define AT_FILESYSTEM_SUPPORT

/* Debug */

/* --- Debug Options --- */

/* --- Register Debug Options --- */

/* --- Profile Options --- */
#define HAL_PROFILE_ON_BUFFER
#define HAL_PROFILING
#define SX_PROFILING
#define PAL_PROFILING
#define VOIS_PROFILING

/* --- Trace Options --- */
#define MMI_NO_TRACE
#define WAP_NO_TRACE
#define MCI_NO_TRACE
#define HAL_NO_PRINTF
#define PAL_NO_TRACE
#define VOIS_NO_PRINTF
#define EDRV_NO_TRACE
#define CALIB_NO_PRINTF
#define UCTLS_NO_PRINTF
#define UMSS_NO_PRINTF
#define ARS_NO_PRINTF
#define RFD_NO_TRACE
#define BT_NO_PRINTF
#define HTTP_NO_TRACE
#define COAP_NO_TRACE
#define LWM2M_NO_TRACE
#define ALIMQTT_NO_TRACE
#define MBEDTLS_NO_TRACE

/* Default */
#define MMI_ON_HARDWARE_P
#define CSD_TARGET
#define CSD_NEW_API

#endif
