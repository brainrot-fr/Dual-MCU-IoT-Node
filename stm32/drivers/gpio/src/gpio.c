#include "gpio.h"

void gpio_clock_enable(GPIO_TypeDef *port){
    uint32_t bit = ((uint32_t)port - AHB1PERIPH_BASE) / 0x400UL;
    RCC->AHB1ENR |= (1U << bit);
}

void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode) {
    port->MODER &= ~(0x3UL << (pin *2));
    port->MODER |= ((uint32_t)mode << (pin * 2));
}

void gpio_toggle(GPIO_TypeDef *port, uint8_t pin) {
    port->ODR ^= (1U << pin);
}