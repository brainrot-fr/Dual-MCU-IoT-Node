#pragma once
#include "stm32f411xe.h"
#include <stdint.h>

typedef enum {
    GPIO_MODE_INPUT  = 0x0,
    GPIO_MODE_OUTPUT = 0x1,
    GPIO_MODE_AF     = 0x2,
    GPIO_MODE_ANALOG = 0x3,
} gpio_mode_t;

void gpio_clock_enable(GPIO_TypeDef *port);
void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode);
void gpio_toggle(GPIO_TypeDef *port, uint8_t pin);