/**
 * @file    gpio.h
 * @author  github.com/brainrot-fr
 * @brief   Public interface for the GPIO helper driver.
 *
 * This header declares the GPIO helper functions and the supported pin modes
 * used by the STM32 firmware application.
 */

#pragma once
#include "stm32f411xe.h"
#include <stdint.h>

typedef enum {
    GPIO_MODE_INPUT  = 0x0,
    GPIO_MODE_OUTPUT = 0x1,
    GPIO_MODE_AF     = 0x2,
    GPIO_MODE_ANALOG = 0x3,
} gpio_mode_t;

/**
 * @brief Enable the clock for the requested GPIO port.
 *
 * @param port Pointer to the GPIO peripheral instance to enable.
 * @return None.
 */
void gpio_clock_enable(GPIO_TypeDef *port);

/**
 * @brief Configure the mode of a single GPIO pin.
 *
 * @param port Pointer to the GPIO peripheral instance.
 * @param pin Zero-based pin number to configure.
 * @param mode Desired operating mode for the pin.
 * @return None.
 */
void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode);

/**
 * @brief Toggle the output state of a GPIO pin.
 *
 * @param port Pointer to the GPIO peripheral instance.
 * @param pin Zero-based pin number to toggle.
 * @return None.
 */
void gpio_toggle(GPIO_TypeDef *port, uint8_t pin);

/**
 * @brief Set (1) the output state of a GPIO pin.
 *
 * @param port Pointer to the GPIO peripheral instance.
 * @param pin Zero-based pin number to toggle.
 * @return None.
 */
void gpio_set(GPIO_TypeDef *port, uint8_t pin);

/**
 * @brief Reset (0) the output state of a GPIO pin.
 *
 * @param port Pointer to the GPIO peripheral instance.
 * @param pin Zero-based pin number to toggle.
 * @return None.
 */
void gpio_reset(GPIO_TypeDef *port, uint8_t pin);