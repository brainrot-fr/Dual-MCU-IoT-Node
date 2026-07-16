/**
 * @file    startup.c
 * @author  github.com/brainrot-fr
 * @brief   Cortex-M startup and reset handling for the STM32 firmware.
 *
 * This file defines the interrupt vector table placed at the start of Flash,
 * provides weak default handlers for exceptions, and performs the reset-time
 * initialization of the .data and .bss sections before jumping to main().
 */

#include <stdint.h>
#define ISR_VECTOR_SIZE_WORDS 114
#define SRAM_START (0x20000000U)
#define SRAM_SIZE (32U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)
#define STACK_POINTER_INIT_ADDRESS (SRAM_END)

void reset_handler(void);
void default_handler(void);
void nmi_handler(void) __attribute__((weak, alias("default_handler")));
void hard_fault_handler(void) __attribute__((weak, alias("default_handler")));
void bus_fault_handler(void) __attribute__((weak, alias("default_handler")));
void usage_fault_handler(void) __attribute__((weak, alias("default_handler")));
void svcall_handler(void) __attribute__((weak, alias("default_handler")));
void debug_monitor_handler(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, alias("default_handler")));
void systick_handler(void) __attribute__((weak, alias("default_handler")));
// continue adding device interrupt handlers

/**
 * @brief Interrupt vector table placed in the .isr_vector section.
 */
uint32_t isr_vector[ISR_VECTOR_SIZE_WORDS] __attribute__((section(".isr_vector"))) = {
  STACK_POINTER_INIT_ADDRESS,
  (uint32_t)&reset_handler,
  (uint32_t)&nmi_handler,
  (uint32_t)&hard_fault_handler,
  (uint32_t)&bus_fault_handler,
  (uint32_t)&usage_fault_handler,
  0,
  0,
  0,
  0,
  0,
  (uint32_t)&svcall_handler,
  (uint32_t)&debug_monitor_handler,
  0,
  (uint32_t)&pendsv_handler,
  (uint32_t)&systick_handler,
  // continue adding device interrupt handlers
};

/**
 * @brief Default exception handler that traps execution if an interrupt is not handled.
 *
 * @return None.
 */
void default_handler(void) {
  while(1);
}

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;
void main(void);

/**
 * @brief Reset handler that copies initialized data from Flash to SRAM and zero-fills .bss.
 *
 * @return None.
 */
void reset_handler(void) {
  // Copy .data from FLASH to SRAM
  uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *flash_data = (uint8_t*) &_etext;
  uint8_t *sram_data = (uint8_t*) &_sdata;
  
  for (uint32_t i = 0; i < data_size; i++) {
    sram_data[i] = flash_data[i];
  }

  // Zero-fill .bss section in SRAM
  uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *bss = (uint8_t*) &_sbss;

  for (uint32_t i = 0; i < bss_size; i++) {
    bss[i] = 0;
  }
  
  main();
}