/**
 * @file    rcc.c
 * @author  github.com/brainrot-fr
 * @brief   RCC helper functions for clock initialization.
 *
 * This file enables the external clock source, configures the PLL, and switches
 * the system clock to the PLL output so the firmware can run at the expected
 * operating frequency.
 */

#include "rcc.h"
#include "stm32f411xe.h"

/**
 * @brief Enable the HSE clock and configure the PLL as the system clock.
 *
 * @return None.
 */
void rcc_clock_enable_pll(void) {

    RCC->CR |= RCC_CR_HSEON_Msk;                            /* enable HSE in crystal mode */
    while (!(RCC->CR & RCC_CR_HSERDY_Msk));                 /* wait until HSE is ready */

    RCC->APB1ENR |= RCC_APB1ENR_PWREN_Msk;                  /* enable power controller */

    volatile uint32_t dummy;
    dummy = RCC_APB1ENR_PWREN;                              /* dummy reads to ensure power is enabled */
    dummy = RCC_APB1ENR_PWREN;                              /* dummy reads to ensure power is enabled */

    PWR->CR |= (0b11 << PWR_CR_VOS_Pos);                    /* power scale mode set to 1 *** 0b11: Scale 1 mode <= 100 MHz */

    FLASH->ACR |= FLASH_ACR_LATENCY_3WS;                    /* Configure flash controller for 100MHz and 3V3 power supply */

    RCC-> PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk |               /* Clear PLL M, N, P bits */
                        RCC_PLLCFGR_PLLN_Msk |
                        RCC_PLLCFGR_PLLP_Msk);

    RCC->PLLCFGR |= ((25 << RCC_PLLCFGR_PLLM_Pos)    |      /* Set PLLM = 25 to get 1MHz as input frequency for PLL */
                    (200 << RCC_PLLCFGR_PLLN_Pos)    |      /* Set PLLN = 200 to get output of VCO as 400MHz as mentioned in the Ref Manual pg.106 */
                    (0b00 << RCC_PLLCFGR_PLLP_Pos)   |      /* Set PLLP = 1 (0b01) to get 100MHz PLL output */
                    (1 << RCC_PLLCFGR_PLLSRC_Pos));         /* Finally, set the HSE as PLL source (0b01 = HSE) */

    RCC->CFGR |= (0b100 << RCC_CFGR_PPRE1_Pos);             /* APB1 Prescaler value is set to 2 (0b100 = 2) to get 50MHz on APB1 */

    RCC->CR |= RCC_CR_PLLON;                                /* enable PLL */ 
    while (!(RCC->CR & RCC_CR_PLLRDY_Msk));                 /* wait until PLL is ready */

    RCC->CFGR |= (RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos);      /* Set PLL output as System Clock */
    while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));                 /* wait until system clock is ready */

}

