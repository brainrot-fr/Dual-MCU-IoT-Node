/**
 * @file    common_includes.h
 * @author  github.com/brainrot-fr
 * @brief   Convenience header that pulls in the common STM32 driver interfaces.
 *
 * This header centralizes the shared includes used by the application so the
 * main firmware source can access the GPIO and RCC helper APIs through one
 * common include.
 */

#include<stdint.h>
#include "gpio.h"
#include "rcc.h"