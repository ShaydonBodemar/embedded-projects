//
// COMP-GENG 422 - Shaydon Bodemar
//
// Output module
//

#include "main.h"
#include "eprintf.h"
#include "sensor.h"
#include "out.h"


#define PROX_QUEUE_RCV_WAIT		portMAX_DELAY	// wait indefinitely


// Global handles
extern QueueHandle_t SensorQueue;	// proximity measurements -> output task


// Task to output the proximity measurement to the serial port
void OutTask(void *pvParameters)
{
	struct SensorData data;

	// Output the legend with four spaces at end for the proximity measurement
	// This initial print no longer necessary, since will be printed on a newline each time now
	// eprintf("Distance:     ");

	while (TRUE)
	{
		// Wait for proximity measurement in queue, then display
		xQueueReceive(SensorQueue, &data, PROX_QUEUE_RCV_WAIT);
		eprintf("Prox: %4dmm -- Temp: %2dC –- Hum: %2d\%\n", data.ProximityMeasurement, data.TemperatureMeasurement, data.HumidityMeasurement);
	}
}
