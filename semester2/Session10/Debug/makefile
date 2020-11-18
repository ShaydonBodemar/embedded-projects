################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/subdir.mk
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
all: Session10.elf

dependents:
	-cd C:/Users/shayd/workspace_Fall2020/b-l475e-iot01a1_hal_lib/Debug && $(MAKE) all

# Tool invocations
Session10.elf: $(OBJS) $(USER_OBJS) C:/Users/shayd/workspace_Fall2020/b-l475e-iot01a1_hal_lib/Debug/libb-l475e-iot01a1_hal_lib.a C:\Users\shayd\workspace_Fall2020\Session10/LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -L"C:\Users\shayd\workspace_Fall2020\b-l475e-iot01a1_hal_lib\Debug" -T"C:/Users/shayd/workspace_Fall2020/Session10/LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "Session10.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "Session10.elf" "Session10.bin"
	arm-none-eabi-size "Session10.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/Users/shayd/workspace_Fall2020/b-l475e-iot01a1_hal_lib/Debug/libb-l475e-iot01a1_hal_lib.a:

-include ../makefile.targets
