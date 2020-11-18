//
// COMP-GENG 422 - Tom Lupfer
//
// Proximity measurement module
//

#include "main.h"
#include "prox.h"


#define PROX_DELAY					100
#define PROX_I2C_ADDRESS			((uint16_t) 0x0052)
#define PROX_QUEUE_SEND_WAIT		0	// no wait

#define VL53L0X_ID					((uint16_t)0xEEAA)
#define VL53L0X_XSHUT_Pin			GPIO_PIN_6
#define VL53L0X_XSHUT_GPIO_Port		GPIOC


extern I2C_HandleTypeDef	hI2cHandler;	// I2C handle
extern QueueHandle_t		ProxQueue;		// proximity measurements -> output task

static VL53L0X_Dev_t Dev =
{
  .I2cHandle = &hI2cHandler,
  .I2cDevAddr = PROX_I2C_ADDRESS
};


void SENSOR_IO_Init(void);

static void VL53L0X_PROXIMITY_Init(void);
static void VL53L0X_PROXIMITY_MspInit(void);
static uint16_t VL53L0X_PROXIMITY_GetDistance(void);


// Task to measure proximity and send the result to the output task
void ProxTask(void *pvParameters)
{
	uint16_t ProxMeasurement;

	VL53L0X_PROXIMITY_Init();

	while (TRUE)
	{
		ProxMeasurement = VL53L0X_PROXIMITY_GetDistance();
		xQueueSendToBack(ProxQueue, &ProxMeasurement, PROX_QUEUE_SEND_WAIT);
		vTaskDelay(PROX_DELAY);
	}
}


// Function to initialize the proximity sensor
static void VL53L0X_PROXIMITY_Init(void)
{
	uint16_t vl53l0x_id = 0;
	VL53L0X_DeviceInfo_t VL53L0X_DeviceInfo;

	// Initialize IO interface
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


// Function to take the proximity sensor out of shutdown
static void VL53L0X_PROXIMITY_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	// Configure GPIO pin : VL53L0X_XSHUT_Pin
	GPIO_InitStruct.Pin = VL53L0X_XSHUT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(VL53L0X_XSHUT_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(VL53L0X_XSHUT_GPIO_Port, VL53L0X_XSHUT_Pin, GPIO_PIN_SET);

	HAL_Delay(1000);
}


// Function to get a proximity measurement
static uint16_t VL53L0X_PROXIMITY_GetDistance(void)
{
	VL53L0X_RangingMeasurementData_t RangingMeasurementData;

	VL53L0X_PerformSingleRangingMeasurement(&Dev, &RangingMeasurementData);

	return RangingMeasurementData.RangeMilliMeter;
}
