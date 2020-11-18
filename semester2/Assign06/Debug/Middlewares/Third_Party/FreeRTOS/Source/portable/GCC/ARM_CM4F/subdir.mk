################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32L4 -DSTM32L475VGTx -DB_L475E_IOT01A1 -DDEBUG -DSTM32L475xx -DUSE_HAL_DRIVER -DUSE_RTOS_SYSTICK -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/HAL_Driver/Inc" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/HAL_Driver/Inc/Legacy" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/ft6x06" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/cs42l51" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/ov9655" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/lis3mdl" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/cs43l22" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/lsm303dlhc" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/stmpe811" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/l3gd20" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/ft3x67" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/iss66wvh8m8" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/st7789h2" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/mx25lm51245g" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/rk043fn48h" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/mfxstm32l152" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/hts221" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/st7735" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/Common" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/n25q256a" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/wm8994" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/stmpe1600" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/mx25r6435f" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/ls016b8uy" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/ft5336" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/lsm303c" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/m24sr" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/n25q128a" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/hx8347g" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/lps22hb" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/Components/lsm6dsl" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/Utilities/B-L475E-IOT01" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/CMSIS/device" -I"/home/shaydon/projects/stm32_workspace/b-l475e-iot01a1_hal_lib/CMSIS/core" -I"/home/shaydon/projects/stm32_workspace/Assign06/inc" -I"/home/shaydon/projects/stm32_workspace/Assign06/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/shaydon/projects/stm32_workspace/Assign06/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/shaydon/projects/stm32_workspace/Assign06/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


