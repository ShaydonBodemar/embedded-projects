//
// COMP-GENG 422 - Shaydon Bodemar
//
// Assignment 03- Program to change LED blink timing based on button push
//

#include "main.h"


#define BUTTON_PUSHED_DELAY		100
#define BUTTON_UNPUSHED_DELAY	1000
#define LED_TASK_STACK_SIZE		1000
#define LED_TASK_PRIORITY		2

#define BUTTON_READ_DELAY		50
#define BUTTON_TASK_STACK_SIZE	100
#define BUTTON_TASK_PRIORITY	1

int LedDelay = BUTTON_UNPUSHED_DELAY;

void LedBlinkTask(void *pvParameters);
void ButtonPushTask(void *pvParameters);
static void SystemClock_Config(void);


int main(void)
{
	// Initialize the hardware and the system clocks
	HAL_Init();
	SystemClock_Config();

	// Initialize LED2
	BSP_LED_Init(LED2);

	// Initialize PB (push button)
	BSP_PB_Init(0, BUTTON_MODE_GPIO); // Should be of format: BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_GPIO);

	// Create the LED blink task
	xTaskCreate(LedBlinkTask,			// Task function
				"LedBlinkTask",			// Task name, for debugging
				LED_TASK_STACK_SIZE,	// Stack size
				NULL,					// Task parameter
				LED_TASK_PRIORITY,		// Task priority
				NULL);					// Task handle

	xTaskCreate(ButtonPushTask,			// Task function
			    "ButtonPushTask",		// Task name for debugging
				BUTTON_TASK_STACK_SIZE,	// Stack size
				NULL,					// Task parameter
				BUTTON_TASK_PRIORITY,	// Task priority
				NULL);					// Task handle

	// Start the scheduler, which never exits
	vTaskStartScheduler();
}


// Task to blink LED2
void LedBlinkTask(void *pvParameters)
{
	while (TRUE)
	{
		BSP_LED_Toggle(LED2);
		vTaskDelay(LedDelay);
	}
}


// Task to read button status
void ButtonPushTask(void *pvParameters)
{
	while(TRUE)
	{
		if(BSP_PB_GetState(0) == GPIO_PIN_RESET) LedDelay = BUTTON_PUSHED_DELAY;
		else LedDelay = BUTTON_UNPUSHED_DELAY;
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
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
								   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
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
