#ifndef __EPD75_DRV_H__
#define __EPD75_DRV_H__

#include "cos.h"

//=======================================================================
// defined
//=======================================================================
#define HSPI    1

#define BLACK           0x00
#define WHITE           0x03
#define RED             0x04
#define GRAY            0x01
#define PINK            0x05

#define SCREEN_WIDTH 		640UL
#define SCREEN_HIGHT 		384UL
#define EPD_BWR_MODE
// #define EPD_BW_MODE 

//=======================================================================
// global parameter
//=======================================================================
enum command{CMD = 0,DAT,};
enum pixel_mode{BW = 0x24,BWR = 0x26,};

//=======================================================================
// function declaration
//=======================================================================
bool EPD75_Init(void);
void spi_init(void);
void byte_send(uint8_t command, const uint8_t *data, uint8_t len);
void HalLcd_TestBWR(byte * displaylist,byte mode);
bool EPD75_fill(byte color, byte ch);
void EPD75_index(char *arg1, char *arg2, char *arg3, char *arg4, 
                 char *arg5, char *arg6, char *arg7, char *arg8);
void EPD75_load(byte *Image, u16 len);
// bool EPD75_show(byte *Image, u16 len);
void EPD75_send(byte color, byte* value, u16 len);
void EPD75_start_load(byte mode);
bool EPD75_check_busy(void);
bool EPD75_update(void);

#endif
