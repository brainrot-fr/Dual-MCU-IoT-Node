/**
 * @file    common_includes.h
 * @author  github.com/brainrot-fr
 * @brief   Convenience header that pulls in the common STM32 driver interfaces.
 *
 * This header centralizes the shared includes used by the application so the
 * main firmware source can access the helper APIs through one
 * common include.
 */
#ifndef COMMON_INCLUDES_H
#define COMMON_INCLUDES_H

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "rcc.h"
#include "usart.h"
#include "stm32f411xe.h"

#endif