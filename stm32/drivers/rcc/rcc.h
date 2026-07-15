/**
 * @file    rcc.h
 * @author  github.com/brainrot-fr
 * @brief   Public interface for the RCC clock configuration helper.
 *
 * This header declares the hardware clock initialization routine used by the
 * application to bring up the STM32 system clock.
 */

#include<stdint.h>

/**
 * @brief Enable the HSE clock and configure the PLL as the system clock.
 *
 * @return None.
 */
void rcc_clock_enable_pll(void);