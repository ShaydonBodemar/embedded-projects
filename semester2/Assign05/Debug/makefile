################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Assign05.elf

dependents:
	-cd /home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Debug && $(MAKE) clean all

# Tool invocations
Assign05.elf: $(OBJS) $(USER_OBJS) /home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Debug/libb-l475e-iot01a1_hal_lib.a /home/shaydon/projects/stm32_workspace/Assign05/LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -L"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Debug" -T"/home/shaydon/projects/stm32_workspace/Assign05/LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "Assign05.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "Assign05.elf" "Assign05.bin"
	arm-none-eabi-size "Assign05.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Debug/libb-l475e-iot01a1_hal_lib.a:

-include ../makefile.targets
