#ifndef _CRC8_H_
#define _CRC8_H_

#include "cos.h"

uint8_t crc8_1byte(uint8_t orign_crc, uint8_t data);
uint8_t crc8_ram(uint8_t *p, uint16_t len);

#endif