#ifndef __TCP_CONF_H__
#define __TCP_CONF_H__

#include "cos.h"
#include "sockets.h"

bool tcp_conf(const char *addr, uint16_t port);
bool tcp_send(uint8_t *data, uint16_t len);

#endif