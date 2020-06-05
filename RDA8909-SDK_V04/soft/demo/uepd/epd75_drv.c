#include "epd75_drv.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "hal_gpio.h"
#include "hal_spi.h"

#include "font.h"


HAL_APO_ID_T cs,dc,power,rst;
u8 color_75 = BLACK;

//=======================================================================
// 
//=======================================================================
#if HSPI
void spi_init(void){
    HAL_SPI_CFG_T spicfg = {
        .enabledCS      = HAL_SPI_CS0,
        .csActiveLow    = TRUE,
        .inputEn        = TRUE,
        .clkFallEdge    = FALSE,//TRUE,
        .clkDelay       = HAL_SPI_HALF_CLK_PERIOD_1,    //first blood
        .doDelay        = HAL_SPI_HALF_CLK_PERIOD_0,
        .diDelay        = HAL_SPI_HALF_CLK_PERIOD_1,
        .csDelay        = HAL_SPI_HALF_CLK_PERIOD_1,
        .csPulse        = HAL_SPI_HALF_CLK_PERIOD_0,
        .frameSize      = 8,
        .oeRatio        = 8,
        .spiFreq        = 1000000, /* 5M 5000000 */
        .rxTrigger      = HAL_SPI_RX_TRIGGER_4_BYTE,
        .txTrigger      = HAL_SPI_TX_TRIGGER_1_EMPTY,
        .rxMode         = HAL_SPI_DIRECT_POLLING,
        .txMode         = HAL_SPI_DIRECT_POLLING,
        .mask           = {0,0,0,0,0},
        .handler        = NULL
    };
    hal_SpiOpen(HAL_SPI, HAL_SPI_CS0, &spicfg);

}

void byte_send(uint8_t command, const uint8_t *data, uint8_t len){
    if(CMD == command){
        hal_GpioClr(dc);
    }
    else if( DAT == command){
        hal_GpioSet(dc);
    }
    hal_SpiActivateCs(HAL_SPI, HAL_SPI_CS0);
    hal_SpiSendData(HAL_SPI, HAL_SPI_CS0, data, len);
    while(!hal_SpiTxFinished(HAL_SPI, HAL_SPI_CS0));    
    hal_SpiDeActivateCs(HAL_SPI, HAL_SPI_CS0);
}
uint8_t byte_read(uint8_t *buf){
    hal_SpiActivateCs(HAL_SPI,HAL_SPI_CS0);
    uint8_t count = hal_SpiGetData(HAL_SPI,HAL_SPI_CS0,buf, 255);
    hal_SpiDeActivateCs(HAL_SPI,HAL_SPI_CS0);
    return count;
}

#else
HAL_APO_ID_T scl, sda;
void spi_init(void){
    scl.gpioId = HAL_GPIO_10;
    hal_GpioSetOut(HAL_GPIO_10);
    hal_GpioSet(scl); 
    sda.gpioId = HAL_GPIO_12;
    hal_GpioSetOut(HAL_GPIO_12);
    hal_GpioSet(sda); 
    COS_Sleep(5);
    hal_GpioClr(scl);
    hal_GpioClr(sda);
}

void byte_send(uint8_t command, const uint8_t *data, uint16_t len){
    uint8_t tmp;
    if(CMD == command){
        hal_GpioClr(dc);
    }
    else if( DAT == command){
        hal_GpioSet(dc);
    }
    hal_GpioClr(cs);
    for(uint16_t i=0;i<len;i++){
        tmp = data[i];
        for(uint8_t j = 0; j < 8; j++){
            hal_GpioClr(scl);
            (tmp & 0x80)?(hal_GpioSet(sda)):(hal_GpioClr(sda));
            tmp <<= 1;
            hal_GpioSet(scl);
        }
    }
    hal_GpioSet(cs);
}
#endif

/********************************************************
 * @ brief: 7.5Inch Epaper Screen Drivers 
 * @ function: init_func / show_func / update_func ...
 ********************************************************/ 
bool EPD75_Init(void){
    power.gpioId = HAL_GPIO_3;
    hal_GpioSetOut(HAL_GPIO_3);
    hal_GpioSet(power); //keep cs is high
    COS_Sleep(20);

    dc.gpioId = HAL_GPIO_2;
    hal_GpioSetOut(HAL_GPIO_2);
    hal_GpioSet(dc); //keep cs is high

    rst.gpioId = HAL_GPIO_1;
    hal_GpioSetOut(HAL_GPIO_1);
    hal_GpioClr(rst);
    COS_Sleep(10);
    hal_GpioSet(rst);
    COS_Sleep(10);
    
    byte_send(CMD, (byte[]){0x06}, 1); //boost setting    
    byte_send(DAT, (byte[]){0xD7, 0xD7, 0x2F}, 3);
    
    COS_Sleep(5);
    byte_send(CMD, (byte[]){0x01}, 1);// power setting   
    byte_send(DAT, (byte[]){0x37, 0x00, 0x09, 0x3F}, 4);
    
    byte_send(CMD, (byte[]){0x04}, 1);//power on  
    COS_Sleep(5);
    
    byte_send(CMD, (byte[]){0x00}, 1);   
    byte_send(DAT, (byte[]){0x0f, 0x00}, 2);//  640*480 起始点在右上角 / 0x07
    
    byte_send(CMD, (byte[]){0x50}, 1);//border     
    byte_send(DAT, (byte[]){0x77}, 1);//w
    
    byte_send(CMD, (byte[]){0x30}, 1);//PLL CONTROL    
    byte_send(DAT, (byte[]){0x3A}, 1);
    
    byte_send(CMD, (byte[]){0x61}, 1);// resolution setting    
    byte_send(DAT, (byte[]){0x02, 0x80, 0x01, 0x80}, 4);//640gate//384source
    
    byte_send(CMD, (byte[]){0x82}, 1);//vcom setting    
    byte_send(DAT, (byte[]){0x1E}, 1);//vcom平均值
     
    byte_send(CMD, (byte[]){0xE5}, 1);   
    byte_send(DAT, (byte[]){0x03}, 1);
    
    return true;
}

void EPD75_load(byte *Image, u16 len){
    for(uint16_t i=0;i<len;i++){
        EPD75_send(color_75, &Image[i], 1);
    }
}
    
bool EPD75_fill(byte color, byte ch){
    EPD75_Init();
    COS_Sleep(5);
    EPD75_start_load(BW);
    for(u16 i=0;i<SCREEN_WIDTH*(SCREEN_HIGHT/8); i++){
        EPD75_load(&ch, 1);
    }
    return EPD75_update();
}

void EPD75_send(byte color, byte* value, u16 len){
    byte ch = 0;
    for(u16 l=0;l<len;l++){
        ch = value[l];
        for(byte i=0;i<4;i++){
            if(0x80 == (ch&0xc0)){       
                byte_send(DAT, (byte[]){(WHITE<<4 | color)}, 1);
            }
            else if(0x40 == (ch&0xc0)){
                byte_send(DAT, (byte[]){(color<<4 | WHITE)}, 1);
            }   
            else if(0xc0 == (ch&0xc0)){
                byte_send(DAT, (byte[]){(WHITE<<4 | WHITE)}, 1);
            }
            else{
                byte_send(DAT, (byte[]){(color<<4 | color)}, 1);
            }
            ch <<= 2;
        }
    }
}

#define ALLLINE_NUM    384
#define EACHLINE_BYTES 80	 //640/8
void HalLcd_TestBWR(byte * displaylist,byte mode)
{
   unsigned int i; 
   byte j,k;   
   byte tempOriginal;  
   unsigned int eachBarbytes,tmpcount;
   EPD75_Init();
   COS_Sleep(5);
   EPD75_start_load(0);	
	
   eachBarbytes=(ALLLINE_NUM/mode)*EACHLINE_BYTES;
   tmpcount=0;
   for(j=0;j<mode;j++){
       tempOriginal=displaylist[j];
       for(i=0;i<eachBarbytes;i++){		
           for(k=0;k<4;k++){		
                   byte_send(DAT, &tempOriginal, 1); 				
           } 
           tmpcount++;	
       }	    	
   }
   EPD75_update();
}

void EPD75_start_load(byte mode){
    byte_send(CMD, (byte[]){0x10}, 1);
}

bool EPD75_check_busy(void){
    byte busy = 1;
    byte cnt = 250;
    byte chip_ID;
    do{
        byte_send(CMD, (byte[]){(0x71)}, 1);
        byte_read(&busy);
        busy &= 0x01;
        COS_Sleep(100);     
    }while(!busy && cnt--);
    byte_send(CMD, (byte[]){0x71}, 1);
    byte_read(&chip_ID);
    chip_ID &= 0x04;  //PON flag
    if(0x04 == chip_ID) return true;
    else    return false;
}

bool EPD75_update(void){     
    byte state = 0;
    byte_send(CMD, (byte[]){0x12}, 1);
    COS_Sleep(2000);
    state = EPD75_check_busy();
    byte_send(CMD, (byte[]){0x02, 0x07}, 2);
    byte_send(DAT, (byte[]){0xA5}, 1);   
    EPD75_check_busy();
    return state;
}

void EPD75_index(char *arg1, char *arg2, char *arg3, char *arg4, 
                 char *arg5, char *arg6, char *arg7, char *arg8){
    byte buf[8][80] = {0};
    byte zero[80];
    byte tmp = 0x00;
    EPD75_Init();
    COS_Sleep(5);
    EPD75_start_load(0);
    memcpy(&buf[0][12], arg1, strlen(arg1));
    memcpy(&buf[1][12], arg2, strlen(arg2));
    memcpy(&buf[2][12], arg3, strlen(arg3));
    memcpy(&buf[3][12], arg4, strlen(arg4));
    memcpy(&buf[4][12], arg5, strlen(arg5));
    memcpy(&buf[5][12], arg6, strlen(arg6));
    memcpy(&buf[6][12], arg7, strlen(arg7));
    memcpy(&buf[7][12], arg8, strlen(arg8));
    for(byte n=0;n<8;n++){
        for(byte i=0;i<32;i++){
            EPD75_send(WHITE, zero, 80);
        }
        for(byte i=0;i<16;i++){
            for(byte j=0;j<80;j++){
                tmp = (0 == buf[n][j])?0xff:~(asc12[buf[n][j]-' '][i]);
                if(n&0x01)
                    EPD75_send(BLACK, &tmp, 1);
                else
                    EPD75_send(RED, &tmp, 1);
            }
        }
    }
    EPD75_update();
}
