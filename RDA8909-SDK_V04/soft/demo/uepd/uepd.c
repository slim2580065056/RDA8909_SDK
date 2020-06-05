/* Copyright (C) 2018 RDA Technologies Limited and/or its affiliates("RDA").
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

#define LOCAL_LOG_TAG MAKE_LOG_TAG('M', 'Y', 'A', 'P')
#include "cos_log.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "cos.h"
#include "vfs.h"

#include "hal_gpio.h"
#include "hal_i2c.h"
#include "hal_spi.h"
#include "hal_uart.h"

#include "hal_ana_gpadc.h"
#include "hal_pwm.h"

#include "epd75_drv.h"
#include "param.h"
#include "protocol.h"

#if TCP_APP
#include "tcp_conf.h"
#endif
#if UDP_APP
#include "udp_conf.h"
#endif

//=======================================================================
// defined 
//=======================================================================
#define BUFFER_LEN	128
#define SLIDE_LEN	512

#define MAX_STRING_LEN	15000 //65536
#define MAX_STRUCT_LEN	6000
#define PIXEL_CNT	4736	//296*(128/8)

#if TCP_APP
#define SERVER_ADDR    "39.108.185.219"
#define SERVER_PORT    (10112)
#endif

#if UDP_APP
#define DES_IPADDR      "39.108.185.219"
#define DES_PORT        (10130)
#endif


//#define  type_len  sizeof(encodeImage29_1)/sizeof(encodeImage29_1[0])
//=======================================================================
// structure and variate
//=======================================================================
typedef struct ENCODE{
	short off;
	unsigned char len;
	unsigned char ch;
}ENCODE_TypeDef;

typedef struct param{
	int strLen;	//解压字符偏移值 
	char str[MAX_STRING_LEN];	//原字符串 
	char slide[SLIDE_LEN];	//滑动窗口大小
	char buf[BUFFER_LEN];	//前向缓冲区 
}param_TypeDef; 

enum {SUCCESS, TIMEOUT, FAIL = -1};

param_TypeDef param;
ENCODE_TypeDef encode_str[MAX_STRUCT_LEN]; 
unsigned char hexArr[PIXEL_CNT];

//========================================================================================================
// function declaration
//========================================================================================================
void new_pic(uint16_t type_len, const unsigned char *pic);
uint16_t str2hex(const char *str, uint16_t len);
void update_slide(int strLen, char *slide);
void decode(uint16_t type_len, const unsigned char *pic);

void testAPP(void);
//========================================================================================================
// function implementations
//========================================================================================================
/*--------------------------------------------------------------------------------------------------------
*   @@ brief packet uncompress 
*   @ Data formatting
*   @ param type_len: tcp/udp recieved data length
*   @ param *pic: tcp/udp recieved string
*   @ param *str: const strings change to hex attay
*   @ param len: the length of const strings, if it's zero len = strlen(str)
*/
void new_pic(uint16_t type_len, const unsigned char *pic){
    for(uint16_t i=0;i<type_len/3;i++){
        encode_str[i].off = ((pic[i*3+1]&0x01)<<8 | pic[i*3])&0x1ff;
        encode_str[i].len = (pic[i*3+1]>>1)&0xff;
        encode_str[i].ch = pic[i*3+2];
    }
    COS_PRINTFI("typeLen:%d",type_len);
    // for(uint16_t i=0;i<type_len/3;i++){
    //     COS_PRINTFI("off:%2x  len:%2x  ch:%c",encode_str[i].off,encode_str[i].len,encode_str[i].ch);
    // }
}

uint16_t str2hex(const char *str, uint16_t len){
    uint16_t cnt=0,i;
	memset(hexArr, 0, PIXEL_CNT);
    if(0 == len){
        len = strlen(str);
    }
    COS_PRINTFI("string length:%d",strlen(str));
	for(i=0;i<len;){
		if(str[i]>='0' && str[i]<='9'){
			hexArr[cnt] = (str[i]-'0');
		}	
		else if(str[i]>='a' && str[i]<='f'){
			hexArr[cnt] = (str[i]-'a'+10);
		}
        else if(str[i]>='A' && str[i]<='F'){
            hexArr[cnt] = (str[i]-'A'+10);
        }
		i += 1;
		
		if(str[i]>='0' && str[i]<='9'){
			hexArr[cnt] = (str[i]-'0') | hexArr[cnt]<<4;
		}	
		else if(str[i]>='a' && str[i]<='f'){
			hexArr[cnt] = (str[i]-'a'+10) | hexArr[cnt]<<4;
		}
        else if(str[i]>='A' && str[i]<='F'){
            hexArr[cnt] = (str[i]-'A'+10) | hexArr[cnt]<<4;
        }
		i += 2;	//空格 
		cnt++;
	}
	return cnt;
}

void update_slide(int strLen, char *slide){
	for(int i=0;i<SLIDE_LEN;i++){	//更新滑动窗口 
		param.slide[SLIDE_LEN-i] = param.str[strLen-i]; 
	}
//	for(i=0;i<8;i++)	//打印调试滑动窗口数据 
//		COS_PRINTFI("%d: %c\t",i,param.slide[i]);
}

void decode(uint16_t type_len, const unsigned char *pic){
	int i,j;
	int struct_len = 0;
	param.strLen = 0;
    new_pic(type_len, pic);
	memset(param.slide, 0, SLIDE_LEN);	//清除缓存 
	struct_len = type_len/3;//sizeof(encode_str)/sizeof(encode_str[0]);	//计算多少组压缩数据 
	for(i=0;i<struct_len;i++){			//循环解析压缩的数据 
		update_slide(param.strLen, param.slide);	//更新滑动窗口 
		for(j=0;j<encode_str[i].len;j++){//根据字典解析出压缩的字符
			param.str[param.strLen++] = param.slide[encode_str[i].off+j];//根据字典、len、offset解析原字符 
			// COS_PRINTFI("i:%d len:%d ch: %x",i,param.strLen, param.slide[encode_str[i].off+j]);
		}
		param.str[param.strLen++] = encode_str[i].ch;		//压缩数据后面的字符 
		// COS_PRINTFI("i:%d len:%d ch: %x",i,param.strLen, encode_str[i].ch);
	}
    uint16_t hexLen = str2hex(param.str, 0);
	COS_PRINTFI("strLen:%d",strlen(param.str));
    COS_PRINTFI("decode str:%s",param.str);
	COS_PRINTFI("hexLen:%d",hexLen);
}

// void tmr_reg(COS_CALLBACK_FUNC_T tm_cb, UINT32 sec){
//     COS_StartCallbackTimer(COS_GetCurrentTaskHandle(), sec * 1000, tm_cb, 0);
// }
// static void tmr_cb(void *param){
//     static int count = 0;
//     count++;
//     COS_PRINTFI("test_timer_cb: %d", count);
//     tmr_reg(tmr_cb, 10);
// }

VOID test_timer(COS_CALLBACK_FUNC_T tm_cb, UINT32 sec)
{
    COS_StartCallbackTimer(COS_GetCurrentTaskHandle(), sec * 1000, tm_cb, 0);
}

static VOID test_timer_cb(void *paramer)
{
    static int count = 0;
    count++;
    COS_PRINTFI("test_timer_cb: %d", count);
    test_timer(test_timer_cb, 10);
}

int app_enter(int argc, char **argv)
{
    COS_PRINTFI("External APP enter");
    
    uint8_t net_sta = 0;
#if TCP_APP
    if(true == tcp_init(SERVER_ADDR, SERVER_PORT))  
        net_sta = 1;
#endif
#if UDP_APP
    if(true == udp_init(DES_IPADDR, DES_PORT))
        net_sta = 1;
#endif    

    testAPP();

    // tmr_reg(tmr_cb, 10);
    // test_timer(test_timer_cb, 10);

    UINT16 vol = get_DevBat();
    COS_PRINTFI("Adc value is %d", vol);
    UINT8 rssi =get_RSSI();
    COS_PRINTFI("RSSI value is %d", rssi);

    epd_index(net_sta);

   	return SUCCESS;
    return 0;
}

void app_exit(void)
{
    COS_PRINTFI("External APP exit");
    return;
}

void testAPP(void){
    uint8_t buf[32];

    memset(buf, 0, 32);
    get_IMEI(buf);
    COS_PRINTFI("IMEI: %s",buf);

    memset(buf, 0, 32);
    get_IMSI(buf);
    COS_PRINTFI("IMSI: %s",buf);

    COS_PRINTFI("RSSI: %d",get_RSSI());

    memset(buf, 0, 32);
    get_OPER(buf);
    COS_PRINTFI("OPER: %s",buf);

    memset(buf, 0, 32);
    get_ICCID(buf);
    COS_PRINTFI("ICCID: %s",buf);

    memset(buf,  0, 32);
    get_DevIDStr(buf);
    COS_PRINTFI("Device ID string: %s", buf);

    memset(buf, 0, 32);
    get_DevID(buf);
    COS_PRINTFI("Device ID: %x %x %x %x",buf[0],buf[1],buf[2],buf[3]);

    memset(buf, 0, 32);
    get_ServADDR(buf);
    COS_PRINTFI("servers addr: %s",buf);

    memset(buf, 0, 32);
    get_ServPORT(buf);
    COS_PRINTFI("servers port: %s",buf);

    p_cmd(0x02, 0x00, 1);
    p_cmd(0x04, 0x01, 0);
    p_cmd(0x04, 0x02, 2);
}