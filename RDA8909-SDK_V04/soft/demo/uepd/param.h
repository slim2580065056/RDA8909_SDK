#ifndef __PARAM_H__
#define __PARAM_H__

#include "cos.h"

// #define OFFSET_DEVID    0
// #define OFFSET_ADDR     9
// #define OFFSET_PORT     13

#define VERSION     "V1.0.0_2018/10/19_test"
#define CINFO       "7.5Inch_640*384_BWR"


void get_IMEI(uint8_t *buf);

void get_IMSI(uint8_t *buf);

char get_RSSI(void);

void get_OPER(uint8_t *buf);

void get_ICCID(uint8_t *buf);

void get_DevID(uint8_t *buf);

void get_DevIDStr(uint8_t *buf);

void get_ServADDR(uint8_t *buf);

void get_ServPORT(uint8_t *buf);

uint16_t get_DevBat(void);

void epd_index(uint8_t init_flag);


#endif
