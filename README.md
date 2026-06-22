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

---

## What is this project

A custom-PCB IoT device focused on **OTA firmware updates** and **register-level drivers** — no Vendor HAL, no Arduino framework.

Features two MCUs: **STM32F411x** (main processor) and **ESP32** (Wi-Fi co-processor), communicating over a UART-based protocol with CRC-16 framing at 115,200 baud.

---

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

---

## Features

- **OTA Firmware Updates** over Wi-Fi via MQTT
- **Register-Level Peripheral Drivers** — UART, SPI, I2C, etc.
- **Register-Level Sensor Drivers** — HC-SR04, BMP280, DHT22, etc.
- **UART Protocol** with CRC-16 framing at 115,200 baud
- **Custom Bootloader** for STM32
- **FreeRTOS** task architecture
- **Custom PCB** design

---

## Repository Structure

---

## Status
- ### ***Completed***: Phase 0.
- ### **Ongoing**:  Phase 1.

## Phase Structure for the project.

### Phase 0: 
 - **ENTRY Gate :  ** 


### Phase 1: 