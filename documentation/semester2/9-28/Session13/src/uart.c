//
// COMP-GENG 422 - Tom Lupfer
//
// UART module
//

#include "main.h"
#include "uart.h"


extern UART_HandleTypeDef hDiscoUart;


// Function to initialize the UART
void UartInit(void)
{
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
}


// Function to output a single character from the UART
int UartCharWrite(int OutChar)
{
	// Write a character to the serial port and wait until it has been sent
	while (HAL_OK != HAL_UART_Transmit(&hDiscoUart, (uint8_t *) &OutChar, 1, 30000))
		;

	return OutChar;
}
