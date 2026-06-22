# Portfolio Project — Session Context

## Status
C pre-curriculum: COMPLETE
Next immediate step: write startup.c, Makefile, flash LED blink on Black Pill (Phase 0 exit gate)

## C Pre-Curriculum — What Was Covered
All five topics taught through hardware context, all confirmed understood:
1. Struct pointer casting — GPIOA->MODER is just (GPIO_TypeDef*)0x40020000 + offset
2. volatile — required on all peripheral registers, missing volatile = optimizer bug in release builds
3. Function pointers — vector table is an array of function pointers, ISR names must match exactly
4. static/const/inline — static for driver-private variables, const keeps data in flash not RAM, inline pastes function body at call site
5. __attribute__ — section() places code at specific memory address, weak() is fallback handler, naked() prevents compiler stack setup (used in HardFault handler)
6. Bitwise operations — set:|=(1U<<n), clear:&=~(1U<<n), toggle:^=(1U<<n), check:&(1U<<n)

## Consolidation Exercise — main.c Status
Written by user, mostly correct. Known issues to fix next session:
- RCC struct missing reserved fields between gaps (0x14→0x20 and 0x24→0x30)
- delay() has i instead of i++ (infinite loop bug)
- MODER should clear bits before setting: &=~(3U<<26) then |=(1U<<26)
- BSRR should use = not |= (write-only register)
- startup.c not written yet — next session task

## Portfolio Plan
Three projects agreed upon:
- P1: Dual-MCU IoT Sensor Node (existing masterplan + DMA, ADC, PWM additions) — IoT/connectivity domain
- P2: STM32 Motor Controller with PID loop — EV/robotics/industrial domain
- P3: CAN-based Fault Monitoring/BMS-lite — automotive/safety-critical domain

Masterplan update discussion: PENDING (happens after LED blink works)

## Hardware
STM32F411 Black Pill, ESP32 DevKit V1, ST-Link V2, DHT22, BMP280, HC-SR04, SSD1306 OLED, logic level shifter, passives

## Toolchain
arm-none-eabi-gcc-cs (Fedora), OpenOCD, ST-Link — all confirmed working
VSCode IntelliSense fix: .vscode/c_cpp_properties.json with intelliSenseMode: gcc-arm

## Claude's Teaching Approach (important for continuity)
- Always teach through hardware context, never abstract examples
- Ask user to reason through answers, not just give them
- Keep responses concise (user on free plan, limited sessions)

