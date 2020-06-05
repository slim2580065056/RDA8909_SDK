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
#include "device_uart.h"

void delay(void)
{
    for(int i = 0; i < 10000; i++);
}

int app_enter(int argc, char **argv)
{
    COS_PRINTFI("External APP enter");
    print_log_init();
    delay();
    app_log_info("Hello world!\r\n");
    app_log_info("Hello world!\r\n");
    app_log_info("Hello world!\r\n");
    delay();
    return 0;
}

void app_exit(void)
{
    print_log_close();
    COS_PRINTFI("External APP exit");
    return;
}
