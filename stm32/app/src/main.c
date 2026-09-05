/**
 * @file    main.c
 * @author  github.com/brainrot-fr
 * @brief   Entry point for the STM32 blink firmware.
 *
 * main file.
 */

#include "common_includes.h"
#include "main.h"
#include "system_stm32f4xx.h"
#include <stdio.h>

/**
 * @brief Counter incremented by the SysTick interrupt handler.
 */
volatile uint32_t ticks;

/**
 * @brief Handle the SysTick interrupt and update the tick counter.
 *
 * @return None.
 */
void systick_handler(void) {
    ticks++;
}

/**
 * @brief Busy-wait for a given number of milliseconds using SysTick ticks.
 *
 * @param milliseconds Number of milliseconds to wait.
 * @return None.
 */
static void delay_ms(uint32_t milliseconds) {
    uint32_t start = ticks;
    uint32_t end = start + milliseconds;

    if (end < start) { /* handle overflow */
        while (ticks > start); /* wait until ticks wrap around to zero */
    }
    while (ticks < end);
}

/**
 * @brief Application entry point.
 *
 * @return This function does not return under normal operation.
 */
int main(void) {
    rcc_clock_enable_pll();

    SysTick_Config(100000);
    __enable_irq();

    rcc_clock_enable_GPIO(GPIOC);
    rcc_clock_enable_GPIO(GPIOA);
    gpio_set_mode(GPIOC, 13, GPIO_MODE_OUTPUT);
    gpio_set_mode(GPIOA, 0, GPIO_MODE_INPUT);

    usart_enable(USART6_PERIPH, APB2_CLK, 115200, GPIOA, 11, 12);

    while (1) {
        printf("HELLO THERE!, this is printed via printf(). %d is an int and %s is a string also %c is a char!", 23, "NAME", 'F');
        delay_ms(1000);
        usart_send_string("HELLO THERE!, this is printed via usart_send_string()!");
    }
    return 0;
}