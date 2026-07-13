TARGET    := blink
BUILD_DIR := build

GCC := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
SIZE    := arm-none-eabi-size

SRC_DIR := src
INC_DIR := inc

# --- driver wiring: add a name here when you create a new driver ---
DRIVERS      := gpio
DRIVERS_ROOT := ../drivers

DRIVER_SRC_DIRS := $(addsuffix /src,$(addprefix $(DRIVERS_ROOT)/,$(DRIVERS)))
DRIVER_INC_DIRS := $(addsuffix /inc,$(addprefix $(DRIVERS_ROOT)/,$(DRIVERS)))

vpath %.c $(SRC_DIR) $(DRIVER_SRC_DIRS)

SRCS := $(wildcard $(SRC_DIR)/*.c) $(foreach d,$(DRIVER_SRC_DIRS),$(wildcard $(d)/*.c))
OBJS := $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.c=.o)))

CFLAGS  := -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=gnu11 \
           -Wall -Wextra -O0 -g -ffreestanding -nostdlib \
           -I$(INC_DIR) $(addprefix -I,$(DRIVER_INC_DIRS))
LDFLAGS := -T linker.ld -nostartfiles -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

COLORS ?= 1

ifeq ($(COLORS),1)
    GREEN 	:= \033[32m
    RED 	:= 	\033[31m
	RESET 	:= \033[0m
else
    GREEN 	:=
	RED		:=
    RESET 	:=
endif

.PHONY: all flash probe clean

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).hex
	@$(SIZE) $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@$(GCC) $(CFLAGS) -c $< -o $@
	@echo -e "[ $(GREEN)BUILDING$(RESET) ]  $@"

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@$(GCC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)
	@echo -e "[ $(GREEN)BUILDING$(RESET) ]  $@"

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	@$(OBJCOPY) -O binary $< $@
	@echo -e "[ $(GREEN)BUILDING$(RESET) ]  $@"

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	@$(OBJCOPY) -O ihex $< $@
	@echo -e "[ $(GREEN)BUILDING$(RESET) ]  $@"

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@echo -e "[ $(GREEN)CREATING$(RESET) ]  build/"

flash: $(BUILD_DIR)/$(TARGET).bin
	@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
	  -c "adapter speed 1000" \
	  -c "transport select hla_swd" \
	  -c "set CPUTAPID 0x2ba01477" \
	  -c "program $(BUILD_DIR)/$(TARGET).bin 0x08000000 verify reset exit"

probe:
	@openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
	  -c "adapter speed 1000" \
	  -c "transport select hla_swd" \
	  -c "set CPUTAPID 0x2ba01477" \
	  -c "init" \
	  -c "reset halt" \
	  -c "exit"

clean:

	@rm -rf $(BUILD_DIR)
	@echo -e "[ $(RED)REMOVED$(RESET) ]  app/build/"

	@rm -rf $(SRC_DIR)/*.o
	@echo -e "[ $(RED)REMOVED$(RESET) ]  app/*.o files..."

	@rm -rf $/*.elf
	@echo -e "[ $(RED)REMOVED$(RESET) ]  app/*.elf files..."

	@rm -rf $/*.map
	@echo -e "[ $(RED)REMOVED$(RESET) ]  app/*.map files..."

