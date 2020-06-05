#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "cos.h"

//use TCP or UDP 
#define TCP_APP     0
#define UDP_APP     1

//vertype
#define VER1_TYPE1      0x11

//cmd
#define READY           0x01
#define HEARTBEAT       0x02
#define PACKET          0x03
#define ESL_STATUS      0x04

//subcmd
#define EN_PSM          0x01
#define EN_DRX          0x02
#define CONF_PSM        0x03
#define RECV_STATUS     0x01
#define UPDATE_STATUS   0x02

#define OFFSET_VER      0
#define OFFSET_CMD      1
#define OFFSET_SUB      2
#define OFFSET_LEN      3
#define OFFSET_CRC      5
#define OFFSET_PAY      6



// typedef struct protocol_t_{
//     uint8_t vertype;
//     uint8_t cmd;
//     uint8_t subcmd;
//     uint16_t len;
//     uint8_t crc;
//     uint8_t *payload;
// }Protocol_TypeDef;

// void protocol_conf(Protocol_TypeDef *param);
void dec2str(uint8_t dec, char *str);
void num2str(uint8_t hex, char *str);
uint8_t str2num(char *str);

void p_cmd(uint8_t cmd, uint8_t subcmd, uint8_t status);

#endif