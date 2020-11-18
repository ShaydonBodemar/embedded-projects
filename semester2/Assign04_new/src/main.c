/**
  ******************************************************************************
  * @file    Proximity/Src/main.c 
  * @author  MCD Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license SLA0044,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <semphr.h>


// SESSION09 defines
#define PROX_DELAY				50
#define PROX_TASK_PRI			1
#define PROX_TASK_STACK			1000

#define BTN_DEBOUNCE_CNT		3
#define BTN_DELAY				25
#define BTN_TASK_PRI			2
#define BTN_TASK_STACK			1000

#define BTN_GPIO_PRESSED		0

#define BTN_ST_RELEASED			0
#define BTN_ST_PRESSED			1
#define BTN_ST_DEBOUNCE			2

#define LED_DELAY_FAST			50
#define LED_DELAY_SLOW			500
#define LED_TASK_PRI			2
#define LED_TASK_STACK			1000

#define SEM_TIMEOUT_NONE		0

SemaphoreHandle_t	BtnSemaphore;



/** @addtogroup STM32L4xx_HAL_Applications
  * @{
  */

/** @addtogroup Proximity
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern I2C_HandleTypeDef hI2cHandler;
VL53L0X_Dev_t Dev =
{
  .I2cHandle = &hI2cHandler,
  .I2cDevAddr = PROXIMITY_I2C_ADDRESS
};

extern UART_HandleTypeDef hDiscoUart;
#ifdef __GNUC__
/* With GCC/RAISONANCE, small msg_info (option LD Linker->Libraries->Small msg_info
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void VL53L0X_PROXIMITY_MspInit(void);
static uint16_t VL53L0X_PROXIMITY_GetDistance(void);
static void VL53L0X_PROXIMITY_Init(void);


// SESSION 09 FUNCTIONS
void ProximityDisplayTask(void *pvParameters);
void LedBlinkTask(void *pvParameters);
void ButtonPressTask(void *pvParameters);
static void SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

  /* STM32L4xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the System clock to have a frequency of 80 MHz */
  SystemClock_Config();

  VL53L0X_PROXIMITY_Init();

  /* Configure the User LED */
  BSP_LED_Init(LED2); 
  
  /* Configure the User Button in GPIO Mode */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  
  /* Initialize all configured peripherals */
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
  

  // SESSION09 CODE
  // Create the semaphore to indicate a button press
  BtnSemaphore = xSemaphoreCreateBinary();

  // Create the button press task
  xTaskCreate(ProximityDisplayTask,	// Task function
				"ProximityDisplayTask",	// Task name, for debugging
				PROX_TASK_STACK,		// Stack size
				NULL,				// Task parameter
				PROX_TASK_PRI,		// Task priority
				NULL);				// Task handle

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


// Task to display proximity readings
void ProximityDisplayTask(void *pvParameters) {
	static uint16_t prox_value = 0;

	while(TRUE) {
		prox_value = VL53L0X_PROXIMITY_GetDistance();
		printf("\rDistance: %4d", prox_value);
		fflush(stdout);

		//vTaskDelay(PROX_DELAY);
	}
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

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 4000000
  *            PLL_M                          = 1
  *            PLL_N                          = 40
  *            PLL_R                          = 2
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* MSI is enabled after System reset, activate PLL with MSI as source */
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
    /* Initialization Error */
    while(1);
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}

/**
  * @brief  Test of VL53L0X proximity sensor.
  */
void Proximity_Test(void)
{
  uint32_t ret = 0;
  uint16_t prox_value = 0;
  
  printf("\n*************************************************************\n");
  printf("\n********************** Proximity Test ************************\n");
  printf("\n*************************************************************\n\n");
  VL53L0X_PROXIMITY_Init();
  printf("\n*** Tape n or N to get a first Proximity distance ***\n\n"); 
  printf("\n*** Tape q or Q to quit Proximity Test ***\n\n"); 
  while(1)
  {
    ret = Serial_Scanf(255);
    if((ret == 'n') || (ret == 'N'))
    {
      printf("\n*** This is a new data ***\n\n");
      prox_value = VL53L0X_PROXIMITY_GetDistance();
      printf("DISTANCE is = %d mm \n", prox_value);
      printf("\n*** This is a new data ***\n\n");
      printf("\n*** Tape n or N to get a new data ***\n\n"); 
      printf("\n*** Tape q or Q to quit Proximity Test ***\n\n");      
    }
    else if((ret == 'q') || (ret == 'Q'))
    {
      printf("\n*** End of Proximity Test ***\n\n");
      return;
    }
    else
    {
      printf("\n*** Tape n or N to get a new data ***\n\n"); 
      printf("\n*** Tape q or Q to quit Proximity Test ***\n\n"); 
    }    
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

/**
  * @brief  Gets numeric values from the Hyperterminal.
  * @param  Maximun value allowed (value)
  * @retval The character received
  */
uint32_t Serial_Scanf(uint32_t value)
{
  uint16_t tmp = 0;
  
  tmp = getchar();
  
  if (tmp > value)
  {
    printf("\n\r  !!! Please enter valid number between 0 and %lu \n", value);
    return 0xFF;
  }
  return tmp;
}

/**
  * @brief Retargets the C library msg_info function to the USART.
  * @param None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the serial port and Loop until the end of transmission */
  while (HAL_OK != HAL_UART_Transmit(&hDiscoUart, (uint8_t *) &ch, 1, 30000))
  {
    ;
  }
  return ch;
}

/**
  * @brief Retargets the C library scanf function to the USART.
  * @param None
  * @retval None
  */
GETCHAR_PROTOTYPE
{
  /* Place your implementation of fgetc here */
  /* e.g. readwrite a character to the USART2 and Loop until the end of transmission */
  uint8_t ch = 0;
  while (HAL_OK != HAL_UART_Receive(&hDiscoUart, (uint8_t *)&ch, 1, 30000))
  {
    ;
  }
  return ch;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{  
  /* User can add his own implementation to report the HAL error return state */
  printf("!!! ERROR !!!\n");
  while(1) 
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
