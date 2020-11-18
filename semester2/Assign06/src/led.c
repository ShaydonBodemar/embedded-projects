//
// COMP-GENG 422 - Tom Lupfer
//
// LED module
//

#include "main.h"
#include "led.h"


#define LED_DELAY_FAST		100
#define LED_DELAY_SLOW		1000

#define BTN_SEM_TIMEOUT_NONE	0	// no wait


// Global handles
extern SemaphoreHandle_t BtnSemaphore;	// button pressed semaphore -> LED task


// Task to blink LED2
void LedBlinkTask(void *pvParameters)
{
	static Bool			LedToggleIsSlow = TRUE;

	// Initialize LED2
	BSP_LED_Init(LED2);

	while (TRUE)
	{
		BSP_LED_Toggle(LED2);
		if (xSemaphoreTake(BtnSemaphore, BTN_SEM_TIMEOUT_NONE) == pdTRUE)
		{
			LedToggleIsSlow = !LedToggleIsSlow;
		}
		vTaskDelay(LedToggleIsSlow ? LED_DELAY_SLOW : LED_DELAY_FAST);
	}
}
