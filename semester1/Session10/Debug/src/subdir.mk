################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/clock.c \
../src/effects.c \
../src/eprintf.c \
../src/gpio.c \
../src/led.c \
../src/main.c \
../src/rgb.c \
../src/stm32l1xx_it.c \
../src/syscalls.c \
../src/system_stm32l1xx.c \
../src/uart.c 

OBJS += \
./src/clock.o \
./src/effects.o \
./src/eprintf.o \
./src/gpio.o \
./src/led.o \
./src/main.o \
./src/rgb.o \
./src/stm32l1xx_it.o \
./src/syscalls.o \
./src/system_stm32l1xx.o \
./src/uart.o 

C_DEPS += \
./src/clock.d \
./src/effects.d \
./src/eprintf.d \
./src/gpio.d \
./src/led.d \
./src/main.d \
./src/rgb.d \
./src/stm32l1xx_it.d \
./src/syscalls.d \
./src/system_stm32l1xx.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L152RCTx -DSTM32L152C_DISCO -DDEBUG -DSTM32L152xC -DUSE_HAL_DRIVER -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/CMSIS/core" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/CMSIS/device" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/HAL_Driver/Inc/Legacy" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/HAL_Driver/Inc" -I"C:/Users/shayd/workspace/stm32l152c-disco_hal_lib/Utilities/STM32L152C-Discovery" -I"C:/Users/shayd/workspace/Session10/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


