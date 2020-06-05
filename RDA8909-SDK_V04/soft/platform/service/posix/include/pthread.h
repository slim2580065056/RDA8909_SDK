#ifndef __PTHREAD_H__
#define __PTHREAD_H__
#include "lwip/sys.h"
#include "sxr_mutx.h"

#define pthread_mutex_t sys_mutex_t
#define pthread_cond_t sys_mutex_t
//#define PTHREAD_MUTEX_INITIALIZER {.id = 0xff}
#define pthread_mutex_init(a,b) sys_mutex_new(a)
#define pthread_mutex_destroy(a) sys_mutex_free(a)
#define pthread_mutex_lock(a) sys_mutex_lock(a)
#define pthread_mutex_unlock(a) sys_mutex_unlock(a)

#define pthread_t HANDLE
#endif
