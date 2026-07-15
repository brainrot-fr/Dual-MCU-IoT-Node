/**
 * @file    main.c
 * @author  github.com/brainrot-fr
 * @brief   Entry point for the STM32 blink firmware.
 *
 * This file initializes the system clock, SysTick timer, and GPIO pin used
 * by the LED blink demo. The main loop toggles the LED on and off at a fixed
 * interval.
 */
#include "stm32f411xe.h"
#include "common_includes.h"
#include "system_stm32f4xx.h"

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
static void delay_ms(uint32_t milliseconds) {    /* Delay for 1 second */
    uint32_t start  = ticks;
    uint32_t end    = start + milliseconds;

    if (end < start) {                  /* handle overflow */
        while(ticks > start);           /* wait until ticks wrap around to zero */
    }
    while(ticks < end);
}

/**
 * @brief Application entry point.
 *
 * @return This function does not return under normal operation.
 */
int main(void)
{
    rcc_clock_enable_pll();

    SysTick_Config(100000);
    __enable_irq();

    gpio_clock_enable(GPIOC);
    gpio_set_mode(GPIOC, 13, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_toggle(GPIOC, 13);
          /* reset -> LED on (active low) */
        delay_ms(1000);
    }
    return 0;
}