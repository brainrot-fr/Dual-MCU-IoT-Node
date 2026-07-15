
/*
 * @file    linker.ld
 * @author  github.com/brainrot-fr
 * @brief   Linker script for the STM32F411 firmware image.
 *
 * This file defines the memory layout for Flash and SRAM, places the interrupt
 * vector table at the start of Flash, and controls where the application's
 * code, initialized data, and zero-initialized data sections are stored.
 */

ENTRY(reset_handler)

MEMORY
{
    FLASH (rx): ORIGIN = 0x08000000, LENGTH = 512K
    SRAM (rwx): ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    .isr_vector : { KEEP(*(.isr_vector)) } >FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    } >FLASH

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } >SRAM AT> FLASH

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    } >SRAM
}