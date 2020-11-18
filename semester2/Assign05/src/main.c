//
// COMP-GENG 422 - Shaydon Bodemar
//
// Assignment 5 - Proximity detection with queue and eprintf
//

#include "main.h"
#include "eprintf.h"


#define BTN_DEBOUNCE_CNT		3
#define BTN_DELAY				25
#define BTN_TASK_PRI			1
#define BTN_TASK_STACK			500

#define BTN_ST_RELEASED			0
#define BTN_ST_PRESSED			1
#define BTN_ST_DEBOUNCE			2

#define LED_DELAY_FAST			100
#define LED_DELAY_SLOW			1000
#define LED_TASK_PRI			1
#define LED_TASK_STACK			500

#define PROX_DELAY				100
#define PROX_TASK_PRI			1
#define PROX_TASK_STACK			1000

#define OUT_DELAY				100
#define OUT_TASK_PRI			1
#define OUT_TASK_STACK			1000

#define SEM_TIMEOUT_NONE		0


extern UART_HandleTypeDef	hDiscoUart;
extern I2C_HandleTypeDef	hI2cHandler;

VL53L0X_Dev_t Dev =
{
  .I2cHandle = &hI2cHandler,
  .I2cDevAddr = PROXIMITY_I2C_ADDRESS
};

SemaphoreHandle_t	BtnSemaphore;
QueueHandle_t		ProxQueue;


int				UartCharWrite(int ch);

static void		ButtonPressTask(void *pvParameters);
static void		LedBlinkTask(void *pvParameters);
static void		ProximityTask(void *pvParameters);
static void		OutputTask(void *pvParameters);
static void		SystemClock_Config(void);
static void		VL53L0X_PROXIMITY_MspInit(void);
static uint16_t	VL53L0X_PROXIMITY_GetDistance(void);
static void		VL53L0X_PROXIMITY_Init(void);


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

	// Create the queue that will pass distance readings to an output function
	ProxQueue = xQueueCreate(10, 4);

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

	// Create the proximity task
	xTaskCreate(ProximityTask,		// Task function
				"ProximityTask",	// Task name, for debugging
				PROX_TASK_STACK,	// Stack size
				NULL,				// Task parameter
				PROX_TASK_PRI,		// Task priority
				NULL);				// Task handle

	// Create the proximity value output task
	xTaskCreate(OutputTask,			// Task function
				"OutputTask",		// Task name, for debugging
				OUT_TASK_STACK,		// Stack size
				NULL,				// Task parameter
				OUT_TASK_PRI,		// Task priority
				NULL);				// Task handle

	// Start the scheduler, which never exits
	vTaskStartScheduler();
}


// Function to output a single character from the UART
int UartCharWrite(int ch)
{
	// Write a character to the serial port and wait until it has been sent
	while (HAL_OK != HAL_UART_Transmit(&hDiscoUart, (uint8_t *) &ch, 1, 30000))
		;

	return ch;
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


// Task to debounce the pushbutton and signal a press
static void ButtonPressTask(void *pvParameters)
{
	static int BtnDebounceCnt;
	static int BtnState = BTN_ST_RELEASED;

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


// Task to blink LED2
static void LedBlinkTask(void *pvParameters)
{
	static Bool			LedToggleIsSlow = TRUE;

	while (TRUE)
	{
		BSP_LED_Toggle(LED2);
		if (xSemaphoreTake(BtnSemaphore, SEM_TIMEOUT_NONE) == pdTRUE)
		{
			LedToggleIsSlow = !LedToggleIsSlow;
		}
		vTaskDelay(LedToggleIsSlow ? LED_DELAY_SLOW : LED_DELAY_FAST);
	}
}


// Task to measure proximity
static void ProximityTask(void *pvParameters)
{
	// Initialize UART
	hDiscoUart.Instance = DISCOVERY_COM1;
	hDiscoUart.Init.BaudRate = 115200;
	hDiscoUart.Init.WordLength = UART_WORDLENGTH_8B;
	hDiscoUart.Init.StopBits = UART_STOPBITS_1;
	hDiscoUart.Init.Parity = UART_PARITY_NONE;
	hDiscoUart.Init.Mode = UART_MODE_TX_RX;
	hDiscoUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	hDiscoUart.Init.OverSampling = UART_OVERSAMPLING_16;
	hDiscoUart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	hDiscoUart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	BSP_COM_Init(COM1, &hDiscoUart);

	VL53L0X_PROXIMITY_Init();
	static int value_in;

	while (TRUE)
	{
		value_in = VL53L0X_PROXIMITY_GetDistance();
		xQueueSendToBack(ProxQueue, &value_in, 0);
		vTaskDelay(PROX_DELAY);
	}
}


// Task to output proximity readings
static void OutputTask(void *pvParameters)
{
	static int prox_reading = 0;
	eprintf("Distance:     ");

	while(TRUE)
	{
		xQueueReceive(ProxQueue, &prox_reading, 100);
		eprintf("\b\b\b\b%4d", prox_reading);
		vTaskDelay(OUT_DELAY);
	}
}


/**
  * @brief  VL53L0X proximity sensor Initialization.
  */
static void VL53L0X_PROXIMITY_Init(void)
{
  uint16_t vl53l0x_id = 0;
  VL53L0X_DeviceInfo_t VL53L0X_DeviceInfo;

  /* Initialize IO interface */
  SENSOR_IO_Init();
  VL53L0X_PROXIMITY_MspInit();

  memset(&VL53L0X_DeviceInfo, 0, sizeof(VL53L0X_DeviceInfo_t));

  if (VL53L0X_ERROR_NONE == VL53L0X_GetDeviceInfo(&Dev, &VL53L0X_DeviceInfo))
  {
    if (VL53L0X_ERROR_NONE == VL53L0X_RdWord(&Dev, VL53L0X_REG_IDENTIFICATION_MODEL_ID, (uint16_t *) &vl53l0x_id))
    {
      if (vl53l0x_id == VL53L0X_ID)
      {
        if (VL53L0X_ERROR_NONE == VL53L0X_DataInit(&Dev))
        {
          Dev.Present = 1;
          SetupSingleShot(Dev);
        }
        else
        {
          printf("VL53L0X Time of Flight Failed to send its ID!\n");
        }
      }
    }
    else
    {
      printf("VL53L0X Time of Flight Failed to Initialize!\n");
    }
  }
  else
  {
    printf("VL53L0X Time of Flight Failed to get infos!\n");
  }
}

/**
  * @brief  Get distance from VL53L0X proximity sensor.
  * @retval Distance in mm
  */
static uint16_t VL53L0X_PROXIMITY_GetDistance(void)
{
  VL53L0X_RangingMeasurementData_t RangingMeasurementData;

  VL53L0X_PerformSingleRangingMeasurement(&Dev, &RangingMeasurementData);

  return RangingMeasurementData.RangeMilliMeter;
}

/**
  * @brief  VL53L0X proximity sensor Msp Initialization.
  */
static void VL53L0X_PROXIMITY_MspInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /*Configure GPIO pin : VL53L0X_XSHUT_Pin */
  GPIO_InitStruct.Pin = VL53L0X_XSHUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(VL53L0X_XSHUT_GPIO_Port, &GPIO_InitStruct);

  HAL_GPIO_WritePin(VL53L0X_XSHUT_GPIO_Port, VL53L0X_XSHUT_Pin, GPIO_PIN_SET);

  HAL_Delay(1000);
}
