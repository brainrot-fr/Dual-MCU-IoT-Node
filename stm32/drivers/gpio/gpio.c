/** 
  *******************************************************************************
  * @file       gpio.c
  * @author     github.com/brainrot-fr
  * @brief      GPIO helper functions for STM32 peripheral access.
  *
  * This file provides small convenience wrappers for enabling the GPIO clock,
  * configuring a pin mode, and toggling a pin output state.
  *******************************************************************************
*/

#include "gpio.h"

/**
 * @brief Enable the clock for the requested GPIO port.
 *
 * @param port Pointer to the GPIO peripheral instance to enable.
 * @return None.
 */
void gpio_clock_enable(GPIO_TypeDef *port){     /* enables clock for the port specified */
    uint32_t bit = ((uint32_t)port - AHB1PERIPH_BASE) / 0x400UL;
    RCC->AHB1ENR |= (1U << bit);
}

/**
 * @brief Configure the mode of a single GPIO pin.
 *
 * @param port Pointer to the GPIO peripheral instance.
 * @param pin Zero-based pin number to configure.
 * @param mode Desired operating mode for the pin.
 * @return None.
 */
void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode) {     /* sets mode for the pin */
    port->MODER &= ~(0x3UL << (pin *2));
    port->MODER |= ((uint32_t)mode << (pin * 2));
}

/**
 * @brief Toggle the output state of a GPIO pin.
 *
 * @param port Pointer to the GPIO peripheral instance.
 * @param pin Zero-based pin number to toggle.
 * @return None.
 */
void gpio_toggle(GPIO_TypeDef *port, uint8_t pin) {     /* toggles a given pin */
    port->ODR ^= (1U << pin);
}