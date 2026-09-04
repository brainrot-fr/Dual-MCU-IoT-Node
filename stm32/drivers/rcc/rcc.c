/**
 * @file    rcc.c
 * @author  github.com/brainrot-fr
 * @brief   RCC helper functions for clock initialization.
 *
 * This file enables the external clock source, configures the PLL, and switches
 * the system clock to the PLL output so the firmware can run at the expected
 * operating frequency.
 */
#include <stddef.h>
#include "common_includes.h"

void rcc_clock_enable_pll(void) {

    RCC->CR |= RCC_CR_HSEON_Msk;                            /* enable HSE in crystal mode */
    while (!(RCC->CR & RCC_CR_HSERDY_Msk));                 /* wait until HSE is ready */

    RCC->APB1ENR |= RCC_APB1ENR_PWREN_Msk;                  /* enable power controller */

    (void)RCC_APB1ENR_PWREN;                                /* dummy reads to ensure power is enabled */
    (void)RCC_APB1ENR_PWREN;                                /* dummy reads to ensure power is enabled */

    PWR->CR |= (0b11 << PWR_CR_VOS_Pos);                    /* power scale mode set to 1 *** 0b11: Scale 1 mode <= 100 MHz */

    FLASH->ACR |= FLASH_ACR_LATENCY_3WS;                    /* Configure flash controller for 100MHz and 3V3 power supply */

    RCC-> PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk |               /* Clear PLL M, N, P bits */
                       RCC_PLLCFGR_PLLN_Msk |
                       RCC_PLLCFGR_PLLP_Msk);

    RCC->PLLCFGR |= ((25 << RCC_PLLCFGR_PLLM_Pos)    |      /* Set PLLM = 25 to get 1MHz as input frequency for PLL */
                    (200 << RCC_PLLCFGR_PLLN_Pos)    |      /* Set PLLN = 200 to get output of VCO as 400MHz Ref Manual pg.106 */
                    (0b00 << RCC_PLLCFGR_PLLP_Pos)   |      /* Set PLLP = 1 (0b01) to get 100MHz PLL output */
                    (1 << RCC_PLLCFGR_PLLSRC_Pos));         /* Finally, set the HSE as PLL source (0b01 = HSE) */

    RCC->CFGR |= (0b100 << RCC_CFGR_PPRE1_Pos);             /* APB1 Prescaler value is set to 2 (0b100 = 2) to get 50MHz on APB1 */

    RCC->CR |= RCC_CR_PLLON;                                /* enable PLL */ 
    while (!(RCC->CR & RCC_CR_PLLRDY_Msk));                 /* wait until PLL is ready */

    RCC->CFGR |= (RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos);      /* Set PLL output as System Clock */
    while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));                 /* wait until system clock is ready */

}

void rcc_clock_enable_GPIO(GPIO_TypeDef *port){
    uint32_t bit = ((uint32_t)port - AHB1PERIPH_BASE) / 0x400UL;
    RCC->AHB1ENR |= (1U << bit);
}

void rcc_usart_enable(usart_peripheral_t usart, GPIO_TypeDef *port, uint8_t tx_pin, uint8_t rx_pin) {

    const usart_config_t *config = NULL;

    // Find the correct config[] for the given params
    for (size_t i = 0; i < sizeof(usart_configs) / sizeof(usart_configs[0]); i++) {
        if (usart_configs[i].usart     ==  usart   &&
            usart_configs[i].port      ==  port    &&
            usart_configs[i].tx_pin    ==  tx_pin  &&
            usart_configs[i].rx_pin    ==  rx_pin) {
                config = &usart_configs[i];
                break;
            }
    }

    rcc_clock_enable_GPIO(port);                               /* Enable Clock for port specified */

    gpio_set_mode(port, tx_pin, GPIO_MODE_AF);             /* Set PA10 mode to Analog Function */
    gpio_set_mode(port, rx_pin, GPIO_MODE_AF);             /* Set PA11 mode to Analog Function */

    uint8_t af = config->af_value;
    port->AFR[tx_pin >> 3] |= (af << ((tx_pin & 0x7) * 4));
    port->AFR[rx_pin >> 3] |= (af << ((rx_pin & 0x7) * 4));

    switch (usart) {

        case USART1_PERIPH:
            RCC->APB2ENR |=  RCC_APB2ENR_USART1EN;  //enable USART1 on APB2 bus
            usart_enable(usart);
            break;
        
        case USART2_PERIPH:
            RCC->APB1ENR |=  RCC_APB1ENR_USART2EN;  //enable USART2 on APB1 bus
            usart_enable(usart);
            break;
        
        case USART6_PERIPH:
            RCC->APB2ENR |=  RCC_APB2ENR_USART6EN;  //enable USART6 on APB2 bus
            usart_enable(usart);
            break;
        
        default: //use USART2 as default
            RCC->APB1ENR |=  RCC_APB1ENR_USART2EN;  //enable USART2 on APB1 bus
            usart_enable(usart);
            break;
    }

    
}
