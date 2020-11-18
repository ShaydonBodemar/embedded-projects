################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/stm32l1xx_it.c \
../src/syscalls.c \
../src/system_stm32l1xx.c 

OBJS += \
./src/main.o \
./src/stm32l1xx_it.o \
./src/syscalls.o \
./src/system_stm32l1xx.o 

C_DEPS += \
./src/main.d \
./src/stm32l1xx_it.d \
./src/syscalls.d \
./src/system_stm32l1xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L152RCTx -DSTM32L152C_DISCO -DDEBUG -DSTM32L152xC -DUSE_HAL_DRIVER -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/CMSIS/core" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/CMSIS/device" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/HAL_Driver/Inc/Legacy" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/HAL_Driver/Inc" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/Utilities/STM32L152C-Discovery" -I"C:/Users/shayd/workspace/Assign01/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


