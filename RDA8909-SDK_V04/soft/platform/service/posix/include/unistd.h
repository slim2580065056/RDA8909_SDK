#ifndef __UNISTD_H__
#define __UNISTD_H__
#include "cs_types.h"
#include "sxs_io.h"
#include "lwipopts.h"

#ifndef __u_char_defined
typedef unsigned long  u_long;
typedef unsigned int   u_int;
typedef unsigned short u_short;
typedef unsigned char  u_char;
#define __u_char_defined
#endif

extern char *optarg;
extern int optind;
extern int opterr;

#define fpos_t int
#define signal(A,B)
typedef int FILE;
#define PRId64 "lu"
#define STDIN_FILENO (void *)0
#define stdout (void *)1
#define stderr (void *)2
#define printf(...) sys_arch_printf(__VA_ARGS__)

#define fflush(...)

int getopt(int nargc, char * const *nargv, const char* ostr);

#define fprintf(a,...) sys_arch_printf(__VA_ARGS__)
#define perror(...) sys_arch_printf(__VA_ARGS__)
#ifndef exit
#define exit(x) do { sys_arch_printf("exit with %d\n",x);return x;} while(0)
#endif

unsigned char *strerror(int error);
int strcasecmp(const char *pcStr2, const char *pcStr1);

#endif
