#ifndef __SYS_TIME_H__
#define __SYS_TIME_H__
#include <cswtype.h>
#include "cfw.h"

//#ifndef _TIME_T_DEFINED
#define _TIME_T_DEFINED
typedef int32_t  time_t;
//#endif

#ifndef _STRUCT_TIMESPEC
#define _STRUCT_TIMESPEC
struct timespec {
    time_t  tv_sec;                 /* seconds */
    uint32_t   tv_nsec;                /* nanoseconds */
};
#endif

struct timeval {
    time_t    tv_sec;         /* seconds */
    uint32_t    tv_usec;        /* and microseconds */
};

struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};

int gettimeofday(struct timeval *tv, struct timezone *tz);
time_t time(time_t* timer);

#endif
