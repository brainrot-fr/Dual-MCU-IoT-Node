#ifndef USART_H
#define USART_H

#include "common_includes.h"

void usart_enable(usart_peripheral_t usart, uint32_t peripheral_clock, uint32_t baud_rate, GPIO_TypeDef *port, uint8_t tx_pin, uint8_t rx_pin);

uint32_t usart_send_char(usart_peripheral_t port, uint8_t data);

static inline bool is_bit_set(volatile uint32_t reg,uint8_t mask){
    return (reg & mask) != 0;
}


#endif