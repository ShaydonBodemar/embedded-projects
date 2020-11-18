/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-27-2020
  *
  * COMP/GENG 421 - Shaydon Bodemar
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
	//volatile keyword prevents optimizer removing this value and the for loops that utilize it
	volatile int DelayCnt;

	//below enables the clock for PORT A
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	//set the desired default value to be 0/1 (in this case setting to high, where ResetOutputPin would be low)
	//LED will thereby be on by default
	//active high peripheral
	//if the LED were tied to Power (3.3V), then the active low configuration will allow illumination
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5);
	//configure the desired pin as an output
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);

	//Main mode
	while(TRUE)
	{
		LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);

		for(DelayCnt = 0; DelayCnt < 20000; DelayCnt++)
			;
		//End - main loop

		LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);

		for(DelayCnt = 0; DelayCnt < 40000; DelayCnt++)
			;
	}
}
