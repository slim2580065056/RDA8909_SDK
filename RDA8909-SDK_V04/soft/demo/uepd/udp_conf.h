#ifndef __UDP_CONF_H__
#define __UDP_CONF_H__

#include "cos.h"
#include "sockets.h"

bool udp_init(const char *addr, uint16_t port);

bool udp_send(uint8_t *data, uint16_t len);


#endif