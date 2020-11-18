################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/accel.c \
../src/adc.c \
../src/clock.c \
../src/eprintf.c \
../src/game.c \
../src/gpio.c \
../src/i2c.c \
../src/lcd.c \
../src/main.c \
../src/nav.c \
../src/rgb.c \
../src/stm32l1xx_it.c \
../src/syscalls.c \
../src/system_stm32l1xx.c \
../src/uart.c 

OBJS += \
./src/accel.o \
./src/adc.o \
./src/clock.o \
./src/eprintf.o \
./src/game.o \
./src/gpio.o \
./src/i2c.o \
./src/lcd.o \
./src/main.o \
./src/nav.o \
./src/rgb.o \
./src/stm32l1xx_it.o \
./src/syscalls.o \
./src/system_stm32l1xx.o \
./src/uart.o 

C_DEPS += \
./src/accel.d \
./src/adc.d \
./src/clock.d \
./src/eprintf.d \
./src/game.d \
./src/gpio.d \
./src/i2c.d \
./src/lcd.d \
./src/main.d \
./src/nav.d \
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
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L152RETx -DNUCLEO_L152RE -DDEBUG -DSTM32L152xE -DUSE_HAL_DRIVER -I"C:/Users/shayd/workspace/nucleo-l152re_hal_lib" -I"C:/Users/shayd/workspace/nucleo-l152re_hal_lib/CMSIS/core" -I"C:/Users/shayd/workspace/nucleo-l152re_hal_lib/CMSIS/device" -I"C:/Users/shayd/workspace/nucleo-l152re_hal_lib/HAL_Driver/Inc/Legacy" -I"C:/Users/shayd/workspace/nucleo-l152re_hal_lib/HAL_Driver/Inc" -I"C:/Users/shayd/workspace/nucleo-l152re_hal_lib/Utilities/STM32L1xx_Nucleo" -I"C:/Users/shayd/workspace/Session26/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


