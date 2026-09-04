/**
 * @file    rcc.h
 * @author  github.com/brainrot-fr
 * @brief   Public interface for the RCC clock configuration helper.
 *
 * This header declares the hardware clock initialization routine used by the
 * application to bring up the STM32 system clock.
 */
#ifndef RCC_H
#define RCC_H

#include <stdint.h>
#include "stm32f411xe.h"

typedef enum {
    USART1_PERIPH,
    USART2_PERIPH,
    USART6_PERIPH
} usart_peripheral_t;

/**
 * @brief datatype struct for usart_configs[]
 */
typedef struct {

    usart_peripheral_t  usart;
    GPIO_TypeDef        *port;

    uint8_t     tx_pin;
    uint8_t     rx_pin;
    uint8_t     af_value;

} usart_config_t;


/**
 * @brief predefined configuration array for rcc_usart_enable()
 */
static const usart_config_t usart_configs[] = {

    { USART1_PERIPH, GPIOA,   9, 10,  7 },      /* USART1, GPIOA, TX, RX, AF_MODE */
    { USART1_PERIPH, GPIOB,   6,  7,  7 },      /* USART1, GPIOB, TX, RX, AF_MODE */
    { USART2_PERIPH, GPIOA,   2,  3,  7 },      /* USART2, GPIOA, TX, RX, AF_MODE */
    { USART2_PERIPH, GPIOD,   5,  6,  7 },      /* USART2, GPIOD, TX, RX, AF_MODE */
    { USART6_PERIPH, GPIOA,  11, 12,  8 },      /* USART6, GPIOA, TX, RX, AF_MODE */
    { USART6_PERIPH, GPIOC,   6,  7,  8 },      /* USART6, GPIOC, TX, RX, AF_MODE */

};

/**
 * @brief Enable the HSE clock and configure the PLL as the system clock.
 */
void rcc_clock_enable_pll(void);

/**
 * @brief Enable the specified USART for communication.
 * 
 * @param usart USART peripheral USART1, USART2, USART6
 * @param port Pointer to the GPIO peripheral instance to enable. GPIOA, GPIOB, GPIOC, GPIOD.
 * @param tx_pin stm32's transmitter pin.
 * @param rx_pin stm32's reciever pin.
 * 
 * @return None.
 */
void rcc_usart_enable(usart_peripheral_t usart, GPIO_TypeDef *port, uint8_t tx_pin, uint8_t rx_pin);

/**
 * @brief Enable the clock for the requested GPIO port.
 *
 * @param port Pointer to the GPIO peripheral instance to enable. GPIOA, GPIOB, GPIOC, GPIOD, etc,.
 * @return None.
 */
void rcc_clock_enable_GPIO(GPIO_TypeDef *port);

#endif