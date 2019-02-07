ARM_GCC_PATH_ROOT="C:\Program Files (x86)\GNU Tools ARM Embedded\8 2018-q4-major"
ARM_GCC_PATH=$(ARM_GCC_PATH_ROOT)\bin

STM32_CUBE_ROOT="C:\Users\matthewb\Documents\work\sandbox\stm32l4\STM32Cube_FW_L4_V1.13.0"
STM32l4_HAL_DRIVER=$(STM32_CUBE_ROOT)\Drivers\STM32L4xx_HAL_Driver
CMSIS_DRIVER=$(STM32_CUBE_ROOT)\Drivers\CMSIS
CMSIS_DEVICE=$(CMSIS_DRIVER)\Device\ST\STM32L4xx

AS=$(ARM_GCC_PATH)\arm-none-eabi-gcc.exe
CC=$(ARM_GCC_PATH)\arm-none-eabi-gcc.exe
LD=$(ARM_GCC_PATH)\arm-none-eabi-gcc.exe

INCLUDE_PATH=-I. -I$(STM32l4_HAL_DRIVER)\inc -I$(CMSIS_DRIVER)\Include -I$(CMSIS_DEVICE)\Include

ARCH_FLAGS=-mthumb -mcpu=cortex-m4
HAL_MACROS=-DSTM32L433xx
CFLAGS=-g3 -Wall -Wpedantic $(ARCH_FLAGS) $(HAL_MACROS) $(INCLUDE_PATH)

bare-metal: main.o reset-handler.o interrupt-vectors.o
	$(LD) -nostdlib -Wl,--script=256kflash-48kram.ld -Wl,-Map=$@.map $^ -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) -o $@ $<

reset-handler.o: reset-handler.s
	$(AS) -c -o $@ $<

interrupt-vectors.o: interrupt-vectors.s
	$(AS) -c -o $@ $<

.PHONY: clean
clean:
	del bare-metal *.o *.map
