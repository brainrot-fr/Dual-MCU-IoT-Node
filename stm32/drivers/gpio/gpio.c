/** 
  *
  * @file       gpio.c
  * @author     github.com/brainrot-fr
  * @brief      GPIO helper functions for STM32 peripheral access.
  *
  * This file provides small convenience wrappers for enabling the GPIO clock,
  * configuring a pin mode, and toggling a pin output state.
  *
*/

#include "common_includes.h"

void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode) {
    port->MODER &= ~(0x3UL << (pin *2));
    port->MODER |= ((uint32_t)mode << (pin * 2));
}

void gpio_toggle(GPIO_TypeDef *port, uint8_t pin) {
    port->ODR ^= (1U << pin);
}

void gpio_set(GPIO_TypeDef *port, uint8_t pin) {
    port->ODR |= (1U << pin);
}

void gpio_reset(GPIO_TypeDef *port, uint8_t pin) {
    port->ODR &= ~(1U << pin);
}