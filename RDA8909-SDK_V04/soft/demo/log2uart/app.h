#ifndef __APP_H__
#define __APP_H__

#if 1
    #define app_log_info(fmt, ...)  print_log("app_info: " fmt, ##__VA_ARGS__)
    #define app_log_err(fmt, ...)   print_log("app_err: " fmt, ##__VA_ARGS__)
    #define app_log_debug(fmt, ...) print_log("app_debug: " fmt, ##__VA_ARGS__)
#else
    #define app_log_info(fmt, ...)
    #define app_log_err(fmt, ...)
    #define app_log_debug(fmt, ...)
#endif


typedef struct app_data_type {
    
} app_data;

#endif
