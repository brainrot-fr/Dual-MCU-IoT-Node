# Dual-MCU-IoT-Node

> Documenting this journey on YouTube as well. *(link coming soon)*

---

## Contents

- [Dual-MCU-IoT-Node](#dual-mcu-iot-node)
  - [Contents](#contents)
  - [What is this project](#what-is-this-project)
  - [Goal of this project](#goal-of-this-project)
  - [Features](#features)
  - [Repository Structure](#repository-structure)
  - [Status](#status)
  - [Phase Structure for the project.](#phase-structure-for-the-project)
    - [Phase 0:](#phase-0)

> See [docs/build.md](docs/build.md) for installation and build instructions.

## What is this project

A custom-PCB IoT device focused on **OTA firmware updates** and **register-level drivers** — no Vendor HAL, no Arduino framework.

Features two MCUs: **STM32F411x** (main processor) and **ESP32** (Wi-Fi co-processor), communicating over a UART-based protocol with CRC-16 framing at 115,200 baud.

## Goal of this project

- Makefile-based build automation
- Linker Script Language and memory layout
- ARM Cortex-M architecture and memory mapping
- Embedded device startup flow through to RTOS/infinite loop
- Register-level peripheral manipulation on STM32/ARM
- Peripheral and sensor drivers at register level
- FreeRTOS task architecture in embedded context
- OTA firmware update pipeline (industry practice)
- PCB design best practices
- Register-level debugging


## Features

- **OTA Firmware Updates** over Wi-Fi via MQTT
- **Register-Level Peripheral Drivers** — UART, SPI, I2C, etc.
- **Register-Level Sensor Drivers** — HC-SR04, BMP280, DHT22, etc.
- **UART Protocol** with CRC-16 framing at 115,200 baud
- **Custom Bootloader** for STM32
- **FreeRTOS** task architecture
- **Custom PCB** design


## Repository Structure
```
Dual-MCU-IoT-Node/
├── docs/
│     └──documents related to the project
├── esp32/
│     ├──
├── files/
│     ├── files for development purpose
├── README.md
├── stm32/
│     ├── app/ // contains files required for stm32
│     │   ├── inc/ 
│     │   │   ├── headerfiles (*.h)
│     │   ├── linker.ld // combines object files and libraries into one single binary
│     │   ├── Makefile // used to automate the build process
│     │   └── src/
│     │       ├── sourcefiles (*.c)
│     ├── bootloader/
│             ├── the bootloader files for STM32 
│     └── startup/
│             ├── startup.s and startup.c for the STM32 
├── STM32 Docs/
      ├── DataSheet.pdf
      ├── Programming Manual.pdf
      └── Reference Manual.pdf
```

## Status
- ### ***Completed***: Phase 0.
- ### **Ongoing**:  Phase 1.

## Phase Structure for the project.

### Phase 0: Foundation
 -  **Entry Gate** : Intermediate C, basic Arduino Experience.
 - **Exit Gate** : Can compile + flash a bare-metal project, ARM memory map understood, repo live.

### Phase 1: STM32 Bare-Metal Peripheral Drivers 
  - **Entry Gate** : Phase 0 Complete, OPENOCD flashes, stm32 vendor datasheets downloaded.
  - **Exit Gate** : UART (ISR ring buffer + printf), GPIO, I2C (BMP280+SSD1306), SPI, Timer IC (HC-SR04), DHT22 all with register-level test harnesses. HardFault handler working

### Phase 2: FreeRTOS + ESP32 Baseline
  - **Entry Gate** : Phase 1 complete. All peripheral drivers tested and committed.
  - **Exit Gate** : STM32 running 6-task FreeRTOS with sensor data in queues. ESP32 publishing live sensor values to MQTT visible in MQTT Explorer.

### Phase 3: Inter-MCU UART Protocol
  - **Entry Gate** : Phase 2 complete. FreeRTOS running. ESP32 publishing to MQTT.
  - **Exit Gate** : STM32 and ESP32 exchanging structured CRC-verified frames. Packet loss and corruption detected, NAK'd, and retransmitted.

### Phase 4: Custom Bootloader + OTA Pipeline
  - **Entry Gate** : Inter-MCU protocol passing all acceptance tests.
  - **Exit Gate** : Push firmware_v2.bin to MQTT from laptop. STM32 receives, flashes, verifies, reboots into new firmware. Zero physical access required.

### Phase 5: System Integration and Hardening
  - **Entry Gate** : All subsystems individually verified.
  - **Exit Gate** : System runs 72 hours continuously without intervention. OTA performed mid-soak. Watchdog enabled and proven. All failure modes handled.

### Phase 6: PCB Design and Fabrication
  - **Entry Gate** : v1.0 system integration complete. Every component's electrical behaviour understood.
  - **Exit Gate** : Fabricated PCB with all subsystems running. OTA verified on custom hardware. 24-hour power-on soak passed