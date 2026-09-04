#ifndef USART_H
#define USART_H

#include "common_includes.h"

void usart_enable(usart_peripheral_t port);

uint32_t usart_send_char(usart_peripheral_t port, uint8_t data);


#endif