#include "../inc/stm32f411xe.h"
#include "../inc/common_includes.h"

static void delay(void)     /* Delay for 1 second */
{
    for (volatile int i = 0; i <= 100000; i++);
}

int main(void)
{
    gpio_clock_enable(GPIOC);
    gpio_set_mode(GPIOC, 13, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_toggle(GPIOC, 13);
          /* reset -> LED on (active low) */
        delay();
    }
    return 0;
}