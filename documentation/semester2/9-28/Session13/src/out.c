//
// COMP-GENG 422 - Tom Lupfer
//
// Output module
//

#include "main.h"
#include "eprintf.h"
#include "out.h"


#define PROX_QUEUE_RCV_WAIT		portMAX_DELAY	// wait indefinitely


// Global handles
extern QueueHandle_t ProxQueue;	// proximity measurements -> output task


// Task to output the proximity measurement to the serial port
void OutTask(void *pvParameters)
{
	uint16_t ProxMeasurement;

	// Output the legend with four spaces at end for the proximity measurement
	eprintf("Distance:     ");

	while (TRUE)
	{
		// Wait for proximity measurement in queue, then display
		xQueueReceive(ProxQueue, &ProxMeasurement, PROX_QUEUE_RCV_WAIT);
		eprintf("\b\b\b\b%4d", ProxMeasurement);
	}
}
