//
// COMP-GENG 422 - Shaydon Bodemar
//
// File renamed to better reflect functionality
//
// Proximity measurement module header file
//

#ifndef PROX_H_
#define PROX_H_

#include <stm32l475e_iot01_tsensor.h>
#include <stm32l475e_iot01_hsensor.h>

#define PROX_QUEUE_ITEM_SIZE	sizeof(struct SensorData)
#define PROX_QUEUE_LENGTH		10
#define PROX_TASK_PRI			1
#define PROX_TASK_STACK			1000


void ProxTask(void *pvParameters);

struct SensorData {
	uint16_t ProximityMeasurement;
	uint16_t TemperatureMeasurement;
	uint16_t HumidityMeasurement;
};

#endif // PROX_H_
