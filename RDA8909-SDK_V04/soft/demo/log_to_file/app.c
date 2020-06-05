#define LOCAL_LOG_TAG MAKE_LOG_TAG('M', 'Y', 'A', 'P')
#include "cos_log.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "vfs.h"
#include "sockets.h"

#include "hal_gpio.h"
#include "hal_i2c.h"
#include "hal_spi.h"
#include "hal_uart.h"
#include "hal_ana_gpadc.h"
#include "hal_pwm.h"

#include "ext_device.h"
#include "ext_sys.h"

#include "app.h"
#include "unit.h"

int app_enter(int argc, char **argv)
{
    COS_PRINTFI("External APP enter");

    uint8_t tmp[0xfff];
    for(uint16_t i=0;i<0xfff;i++){
        tmp[i] = i & 0xff;
    }

    print_log_init();
    app_log_info("Hello world!\n");
    for(uint16_t i=0;i<0xfff;i++){
        app_log_info("[%x]:%d  ",i, tmp[i]);
    }
    print_log_close();
    return 0;
}

void app_exit(void)
{
    COS_PRINTFI("External APP exit");
    return;
}
