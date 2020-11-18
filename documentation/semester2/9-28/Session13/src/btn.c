//
// COMP-GENG 422 - Tom Lupfer
//
// User pushbutton module
//

#include "main.h"
#include "btn.h"


#define BTN_DEBOUNCE_CNT		3
#define BTN_DELAY				25

#define BTN_ST_RELEASED			0
#define BTN_ST_PRESSED			1
#define BTN_ST_DEBOUNCE			2


// Global handles
extern SemaphoreHandle_t BtnSemaphore;	// button pressed semaphore -> LED task


// Task to debounce the pushbutton and signal a press
void BtnPressTask(void *pvParameters)
{
	static int BtnDebounceCnt;
	static int BtnState = BTN_ST_RELEASED;

	// Initialize the user pushbutton
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);;

	while (TRUE)
	{
		switch (BtnState)
		{
		case BTN_ST_RELEASED:
			if (!BSP_PB_GetState(BUTTON_USER))		// pushbutton is pressed
			{
				BtnDebounceCnt = BTN_DEBOUNCE_CNT;
				BtnState = BTN_ST_DEBOUNCE;
			}
			break;

		case BTN_ST_PRESSED:
			if (BSP_PB_GetState(BUTTON_USER))		// pushbutton is released
			{
				BtnDebounceCnt = BTN_DEBOUNCE_CNT;
				BtnState = BTN_ST_DEBOUNCE;
			}
			break;

		case BTN_ST_DEBOUNCE:
			if (--BtnDebounceCnt >= 0)				// wait debounce period
			{
				break;
			}
			if (!BSP_PB_GetState(BUTTON_USER))		// pushbutton is pressed
			{
				xSemaphoreGive(BtnSemaphore);		// signal that the pushbutton has been pressed
				BtnState = BTN_ST_PRESSED;
			}
			else									// pushbutton is released
			{
				BtnState = BTN_ST_RELEASED;
			}
			break;
		}

		vTaskDelay(BTN_DELAY);
	}
}
