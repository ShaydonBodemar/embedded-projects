################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32l152xc.s 

OBJS += \
./startup/startup_stm32l152xc.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/CMSIS/core" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/CMSIS/device" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/HAL_Driver/Inc/Legacy" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/HAL_Driver/Inc" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/Utilities/STM32L152C-Discovery" -I"C:/Users/shayd/workspace/Session10/inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


