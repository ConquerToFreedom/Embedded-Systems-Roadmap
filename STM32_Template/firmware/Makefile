###############################################################################
# Project Configuration
###############################################################################

CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

TARGET  = main
MCU     = cortex-m4

# Shared UART driver (relative to this Makefile)
UART_DRIVER_DIR = ../../uart_driver

# Include paths: "." for local stm32f446xx.h, driver dir for uart.h
INCLUDES = -I. -I$(UART_DRIVER_DIR)

CFLAGS  = -mcpu=$(MCU) -mthumb -std=gnu11 -O0 -g3 -Wall -Wextra \
          $(INCLUDES) -MMD -MP
LDFLAGS = -nostdlib -T stm32f446re.ld

###############################################################################
# Source Files
###############################################################################

LOCAL_SRCS  = main.c startup_stm32f446re.c
SHARED_SRCS = $(UART_DRIVER_DIR)/uart.c

SRCS = $(LOCAL_SRCS) $(SHARED_SRCS)

# All .o files go into build/ so the shared uart_driver/ folder stays clean
BUILD_DIR = build
OBJS      = $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.c=.o)))

# Let make find .c files in the source directories
vpath %.c $(sort $(dir $(SRCS)))

###############################################################################
# Build
###############################################################################

all: $(TARGET).elf $(TARGET).bin $(TARGET).hex

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

###############################################################################
# Clean
###############################################################################

clean:
	-rmdir /S /Q $(BUILD_DIR) 2>NUL
	-del /Q $(TARGET).elf $(TARGET).bin $(TARGET).hex 2>NUL

rebuild: clean all

###############################################################################
# Auto-generated dependency files
###############################################################################

-include $(OBJS:.o=.d)

.PHONY: all clean rebuild