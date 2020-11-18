/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-27-2020
  *
  * COMP/GENG 421 - Tom Lupfer
  *
  * Session 1 - GPIO configuration and use
  *
  * GPIO A5 -> Green LED (active high)
  *
  ******************************************************************************
*/


#include "stm32l1xx.h"
//#include "stm32l1xx_nucleo.h"
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_gpio.h"

//					^ ell ell --> low-level driver
//			   ^ ell one -------> STM32L1xx family of microprocessors

#define FALSE	0
#define TRUE	1
			

int main(void)
{
	volatile int DelayCnt;

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);

	//Main mode
	while(TRUE)
	{
		LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);

		for(DelayCnt = 0; DelayCnt < 20000; DelayCnt++)
			;
		//End - main loop
	}
}
