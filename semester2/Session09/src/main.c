//
// COMP-GENG 422 - Tom Lupfer
//
// Session 9 - Use of a semaphore
//

#include "main.h"
#include <semphr.h>


#define BTN_DEBOUNCE_CNT		3
#define BTN_DELAY				25
#define BTN_TASK_PRI			1
#define BTN_TASK_STACK			1000

#define BTN_GPIO_PRESSED		0

#define BTN_ST_RELEASED			0
#define BTN_ST_PRESSED			1
#define BTN_ST_DEBOUNCE			2

#define LED_DELAY_FAST			50
#define LED_DELAY_SLOW			500
#define LED_TASK_PRI			1
#define LED_TASK_STACK			1000

#define SEM_TIMEOUT_NONE		0


SemaphoreHandle_t	BtnSemaphore;


void LedBlinkTask(void *pvParameters);
void ButtonPressTask(void *pvParameters);
static void SystemClock_Config(void);


int main(void)
{
	// Initialize the hardware and the system clocks
	HAL_Init();
	SystemClock_Config();

	// Initialize LED2
	BSP_LED_Init(LED2);

	// Initialize the user pushbutton
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	// Create the semaphore to indicate a button press
	BtnSemaphore = xSemaphoreCreateBinary();

	// Create the button press task
	xTaskCreate(ButtonPressTask,	// Task function
				"ButtonPressTask",	// Task name, for debugging
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

	// Start the scheduler, which never exits
	vTaskStartScheduler();
}


// Task to debounce the pushbutton and signal a press
void ButtonPressTask(void *pvParameters)
{
	static int BtnDebounceCnt;
	static int BtnState = BTN_ST_RELEASED;

	while (TRUE)
	{
		switch (BtnState)
		{
		case BTN_ST_RELEASED:
			if (BSP_PB_GetState(BUTTON_USER) == BTN_GPIO_PRESSED)	// pushbutton is pressed
			{
				BtnDebounceCnt = BTN_DEBOUNCE_CNT;
				BtnState = BTN_ST_DEBOUNCE;
			}
			break;

		case BTN_ST_PRESSED:
			if (BSP_PB_GetState(BUTTON_USER) != BTN_GPIO_PRESSED)	// pushbutton is released
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
			if (BSP_PB_GetState(BUTTON_USER) == BTN_GPIO_PRESSED)	// pushbutton is pressed
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


// Task to blink LED2
void LedBlinkTask(void *pvParameters)
{
	static Bool LedBlinkIsSlow = TRUE;

	while (TRUE)
	{
		BSP_LED_Toggle(LED2);
		if (xSemaphoreTake(BtnSemaphore, SEM_TIMEOUT_NONE) == pdTRUE)
		{
			LedBlinkIsSlow = !LedBlinkIsSlow;
		}
		vTaskDelay(LedBlinkIsSlow ? LED_DELAY_SLOW : LED_DELAY_FAST);
	}
}


//
// System Clock Configuration
//
//	System Clock source		= PLL (MSI)
//	SYSCLK(Hz)				= 80000000
//	HCLK(Hz)				= 80000000
//	AHB Prescaler			= 1
//	APB1 Prescaler			= 1
//	APB2 Prescaler			= 1
//	MSI Frequency(Hz)		= 4000000
//	PLL_M					= 1
//	PLL_N					= 40
//	PLL_R					= 2
//	PLL_P					= 7
//	PLL_Q					= 4
//	Flash Latency(WS)		= 4
//
static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	// MSI is enabled after System reset, activate PLL with MSI as source
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 40;
	RCC_OscInitStruct.PLL.PLLR = 2;
	RCC_OscInitStruct.PLL.PLLP = 7;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		while (TRUE)	// hang if there is an initialization error
			;
	}

	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clock dividers
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
		while (TRUE)	// hang if there is an initialization error
			;
	}
}
