//
// COMP-GENG 422 - Shaydon Bodemar
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

// For some reason, I always end up having to change this from "freertos.h" to "FreeRTOS.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"


#define FALSE	0
#define TRUE	1


typedef int		Bool;	// Boolean

#endif // MAIN_H_
