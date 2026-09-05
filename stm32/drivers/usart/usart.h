#ifndef USART_H
#define USART_H

#include "common_includes.h"

void usart_enable ( 
     usart_peripheral_t usart,  
     uint32_t peripheral_clock,  
     uint32_t baud_rate,  
     GPIO_TypeDef *port,  
     uint8_t tx_pin,  
     uint8_t rx_pin
);

void usart_set_console(usart_peripheral_t usart);

void usart_send_char(uint8_t data);

void usart_send_string(const char *str);

static inline bool is_bit_set( volatile uint32_t reg,  uint8_t mask){
    return (reg & mask) != 0;
}

#endif