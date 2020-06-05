#include "param.h"
#include "ext_device.h"
#include "ext_sys.h"
#include "hal_ana_gpadc.h"
#include "vfs.h"
#include "hal_spi.h"
#include "protocol.h"
#include "epd75_drv.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct at_setting_oem_s
{
    uint8_t gmi[32];
    uint8_t gmm[32];
    uint8_t gmr[32];
    uint8_t sn[32]; //Device ID Address
    uint8_t hwver[32];
} at_setting_oem_t;


at_setting_oem_t sn;

#define OFFSET_ID       0
#define OFFSET_ADDR     8
#define OFFSET_PORT     23
/*---------------------
*   sn.sn[32] 
*   sn.sn[0-8]   8bytes is Device ID info
*   sn.sn[9-12]  4bytes is Servers Address
*   sn.sn[13-14] 2bytes is Servers Port
*/
/*--------------------------------------------------------------------------------------------------------
*   @@ brief get same infomation
*   @ get system paramer
*   @ param 
*/
void get_IMEI(uint8_t *buf){
    ext_device_getIMEI(buf, 32);
}

void get_IMSI(uint8_t *buf){
    ext_device_getIMSI(buf, 32);
}

char get_RSSI(void){
    return ext_sys_getRSSI();
}

void get_OPER(uint8_t *buf){
    ext_sys_getOper(buf, 32);
}

void get_ICCID(uint8_t *buf){
    ext_device_getICCID(buf, 32);
}

//return hex array
void get_DevID(uint8_t *buf){
    vfs_sfile_read("AT_CFG_OEM.BIN", &sn, sizeof(at_setting_oem_t));
    uint8_t tmp[5] = {0};
    for(uint8_t i=0;i<4;i++){
        tmp[0] = sn.sn[2*i];
        tmp[1] = sn.sn[2*i+1];
        buf[i] = str2num(tmp);
    }
}

void get_DevIDStr(uint8_t *buf){
    vfs_sfile_read("AT_CFG_OEM.BIN", &sn, sizeof(at_setting_oem_t));
    memcpy(buf, &sn.sn[OFFSET_ID], 8);
}

//return string of servers addr
void get_ServADDR(uint8_t *buf){
    vfs_sfile_read("AT_CFG_OEM.BIN", &sn, sizeof(at_setting_oem_t));
    memcpy(buf, &sn.sn[OFFSET_ADDR], 15);
    //"xxx.xxx.xxx.xxx"
}

void get_ServPORT(uint8_t *buf){
    vfs_sfile_read("AT_CFG_OEM.BIN", &sn, sizeof(at_setting_oem_t));
    memcpy(buf, &sn.sn[OFFSET_PORT], 5);    //MAX 65536 
}

uint16_t get_DevBat(void){
    uint32_t tot = 0;
    uint16_t vol = 0, min = 0, tmp = 0;
    hal_GpadcEnableChannel(HAL_ANA_GPADC_CHAN_0);
    hal_GpadcSetMinAtp(HAL_ANA_GPADC_ATP_1S);
    for(uint8_t i=0;i<11;i++){
        tmp = hal_GpadcGetMVol(HAL_ANA_GPADC_CHAN_0);
        if( tmp < min){
            min = tmp;
        }
        tot += tmp;
        COS_Sleep(100);
    }
    vol = (tot-min)/10;
    return vol;
}

void epd_index(uint8_t init_flag){
    uint8_t tmp_buf[30];
    uint8_t id[30]={0}, IP[30]={0}, port[10]={0}, imei[30]={0}, imsi[30]={0}, oper[30]={0}, net_sta[30]={0}, ver[40]={0}, csize[40]={0};

    memset(tmp_buf, 0, 30);
    get_DevIDStr(tmp_buf);
    sprintf(id, "Device ID: %s",tmp_buf);

    memset(tmp_buf, 0, 30);
    get_ServADDR(tmp_buf);
    sprintf(IP, "IP/Port: %s",tmp_buf);
    get_ServPORT(port);
    sprintf(IP, "%s:%s",IP,port);

    memset(tmp_buf, 0, 30);
    get_IMEI(tmp_buf);
    sprintf(imei, "IMEI: %s",tmp_buf);

    memset(tmp_buf, 0, 30);
    get_IMSI(tmp_buf);
    sprintf(imsi, "IMSI: %s",tmp_buf);

    memset(tmp_buf, 0, 30);
    get_OPER(tmp_buf);
    sprintf(oper, "OPER: %s",tmp_buf);

    sprintf(ver, "VERSION: %s",VERSION);

    sprintf(csize, "Size Info: %s",CINFO);

#if TCP_APP
    if(init_flag)  memcpy(net_sta, "TCP init success!", 20);
    else    memcpy(net_sta, "TCP init failed!", 20);
#endif
#if UDP_APP
    if(init_flag)  memcpy(net_sta, "UDP init success!", 20);
    else    memcpy(net_sta, "UDP init failed!", 20);
#endif   

    spi_init();

    EPD75_Init();
    EPD75_index(id, IP, imei, imsi, oper, net_sta, ver, csize);

    hal_SpiClose(HAL_SPI, HAL_SPI_CS0);
}