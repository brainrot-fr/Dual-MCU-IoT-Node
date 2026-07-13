#include <stdint.h>

// 1. Declare main()
// 2. Write Reset_Handler — calls main()
// 3. Write minimal vector table using __attribute__((section(".isr_vector")))
//    needs: stack top (0x20020000), Reset_Handler
//    use __attribute__((weak)) on Reset_Handler

int main(void);
extern void SystemInit(void);

__attribute__((weak)) void Reset_Handler(void) {
    main();
    SystemInit();
}

__attribute__((section(".isr_vector"))) void (*const vector_table[])(void) = {
    (void (*)(void))0x20020000, // Stack top (SRAM end)
    Reset_Handler,              // Reset handler
    // Other Handlers here...
};