#include "../inc/stm32f411xe.h"

static void delay(void)     /* Delay for 1 second */
{
    for (volatile int i = 0; i <= 1000000; i++);
}

static void clock_enable_gpioc(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;    /* Enable clock for GPIOC */
}

static void set_moder_pc13_output(void)
{
    GPIOC->MODER &= ~GPIO_MODER_MODER13;   /* clear GPIOC first */
    GPIOC->MODER |= GPIO_MODER_MODER13_0;  /* set as output */
}

int main(void)
{
    clock_enable_gpioc();
    set_moder_pc13_output();

    while (1) {
        GPIOC->ODR ^= GPIO_ODR_OD13;  /* reset -> LED on (active low) */
        delay();
    }
    return 0;
}