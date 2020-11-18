//
// COMP-GENG 422 - Tom Lupfer
//
// General header file
//

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32l4xx_hal.h"
#include "stm32l475e_iot01.h"

#include "vl53l0x_def.h"
#include "vl53l0x_api.h"
#include "vl53l0x_tof.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


#define FALSE	0
#define TRUE	1

#define PROXIMITY_I2C_ADDRESS	((uint16_t)0x0052)
#define VL53L0X_ID				((uint16_t)0xEEAA)
#define VL53L0X_XSHUT_Pin		GPIO_PIN_6
#define VL53L0X_XSHUT_GPIO_Port	GPIOC


typedef int		Bool;	// Boolean

extern void     SENSOR_IO_Init(void);

void Proximity_Test(void);
uint32_t Serial_Scanf(uint32_t value);
void Error_Handler(void);

#endif // MAIN_H_
