//
// COMP-GENG 422 - Tom Lupfer
//
// Session 13 - Modularization by function and task
//

#include "main.h"
#include "btn.h"
#include "clock.h"
#include "led.h"
#include "out.h"
#include "prox.h"
#include "uart.h"


// Global handles
SemaphoreHandle_t	BtnSemaphore;	// button pressed semaphore -> LED task
QueueHandle_t		ProxQueue;		// proximity measurements -> output task


int main(void)
{
	// Initialize the hardware
	HAL_Init();
	ClockConfig();
	UartInit();

	// Create the semaphore to indicate a button press
	BtnSemaphore = xSemaphoreCreateBinary();

	// Create the queue for proximity measurement output
	ProxQueue = xQueueCreate(PROX_QUEUE_LENGTH, PROX_QUEUE_ITEM_SIZE);

	// Create the button press task
	xTaskCreate(BtnPressTask,		// Task function
				"BtnPressTask",		// Task name, for debugging
				BTN_TASK_STACK,		// Stack size
				NULL,				// Task parameter
				BTN_TASK_PRI,		// Task priority
				NULL);				// Task handle

	// Create the LED blink task
	xTaskCreate(LedBlinkTask,		// Task function
				"LedBlinkTask",		// Task name, for debugging
				LED_TASK_STACK,		// Stack size
				NULL,				// Task parameter
				LED_TASK_PRI,		// Task priority
				NULL);				// Task handle

	// Create the output task
	xTaskCreate(OutTask,			// Task function
				"OutTask",			// Task name, for debugging
				OUT_TASK_STACK,		// Stack size
				NULL,				// Task parameter
				OUT_TASK_PRI,		// Task priority
				NULL);				// Task handle

	// Create the proximity task
	xTaskCreate(ProxTask,			// Task function
				"ProxTask",			// Task name, for debugging
				PROX_TASK_STACK,	// Stack size
				NULL,				// Task parameter
				PROX_TASK_PRI,		// Task priority
				NULL);				// Task handle

	// Start the scheduler, which never exits
	vTaskStartScheduler();
}
