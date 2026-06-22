// 1. Define RCC and GPIOC structs yourself (volatile, correct fields)
// RCC base: 0x40023800, AHB1ENR offset: 0x30 
// GPIOC base: 0x40020800, MODER offset: 0x00, BSRR offset: 0x18

// 2. Define GPIOC and RCC pointers using struct casting

// 3. Write a static delay function (dumb loop, no SysTick yet)

// 4. Write main() — enable GPIOC clock, set PC13 as output, blink forever
// PC13 is the onboard LED on Black Pill (active LOW)

#include <stdint.h>

typedef struct {    /* GPIO Register Definitons with offsets */

    volatile uint32_t MODER;      //  0x00 offest
    volatile uint32_t OTYPER;     //  0x04 offset
    volatile uint32_t OSPEEDR;    //  0x08 offset
    volatile uint32_t PUPDR;      //  0x0C offset
    volatile uint32_t IDR;        //  0x10 offset
    volatile uint32_t ODR;        //  0x14 offset
    volatile uint32_t BSRR;       //  0x18 offset
    volatile uint32_t LCKR;       //  0x1C offset
    volatile uint32_t AFRL;       //  0x20 offset
    volatile uint32_t AFRH;       //  0x24 offset
    
    // I referred the Reference manual for all the registers.

} GPIO_TypeDef;


typedef struct {    /* RCC Register Definitions with offsets */

    // there are a lot of registers for RCC so i directly wrote only ones necessary.

    volatile uint32_t CR;         //  0x00 offset
    volatile uint32_t PLLCFGR;    //  0x04 offset
    volatile uint32_t CFGR;       //  0x08 offset
    volatile uint32_t CIR;        //  0x0C offset
    volatile uint32_t AHB1RSTR;   //  0x10 offset
    volatile uint32_t AHB2RSTR;   //  0x14 offset
    uint32_t RESERVED0[2];        //  0x18 and 0x1C offsets
    volatile uint32_t APB1RSTR;   //  0x20 offset
    volatile uint32_t APB2RSTR;   //  0x24 offset
    uint32_t RESERVED0[2];        //  0x28 and 0x2C offsets
    volatile uint32_t AHB1ENR;    //  0x30 offset

    // many more.. but this is sufficient i hope.

} RCC_TypeDef;


#define GPIO_BASE 0x40020800UL
#define RCC_BASE 0x40023800UL

#define GPIOC ((GPIO_TypeDef *)GPIO_BASE)

#define RCC ((RCC_TypeDef *)RCC_BASE)

void delay(void){
    for (volatile int i = 0; i <= 1000000; i++);
}

void clock_enable_gpioc(void){
    RCC->AHB1ENR |= (1U << 2);
}

void set_moder(void){
    GPIOC->MODER &= ~(3U << 26);
    GPIOC->MODER |= (1U << 26);
}
int main(void) {
    // your code
    clock_enable_gpioc();
    set_moder();

    while(1){

        GPIOC->BSRR |= (1U << 13);

        delay();

        GPIOC->BSRR |= (1U << 29);

        delay();
    }
    return 0;
}