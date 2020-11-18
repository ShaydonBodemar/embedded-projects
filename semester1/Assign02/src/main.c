/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    02-15-2020
  *
  * COMP/GENG 421 - Shaydon Bodemar
  *
  * Assignment 2 - PWM variation based on button push FSM
  *
  * GPIO A5 -> Green LED (active high)
  *
  ******************************************************************************
*/


#include "stm32l1xx.h"
//#include "stm32l1xx_nucleo.h"
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_gpio.h"a

//					^ ell ell --> low-level driver
//			   ^ ell one -------> STM32L1xx family of microprocessors

#define FALSE	0
#define TRUE	1

#define BTN_IS_PRESSED()	(!LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13))	//active low

#define DBG_CLR()			(LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6))
#define DBG_SET()			(LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_6))

#define LED_ENA()			(LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5))	//active high
#define LED_DIS()			(LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5))	//active high

#define LED_TICKS_OFF_HI	1
#define LED_TICKS_ON_HI		9
#define LED_TICKS_OFF_LO	8
#define LED_TICKS_ON_LO		2

#define LED_ST_OFF			0
#define LED_ST_ON			1

#define TICK_DLY_CNT		200


void GpioInit(void);
void LedClock(void);


int main(void)
{
	volatile int	TickCnt;

	// Initialize the hardware
	GpioInit();

	// Main loop
	while(TRUE)
	{
		// Delay for a 1 msec state machine tick
		for (TickCnt = 0; TickCnt < TICK_DLY_CNT; TickCnt++)
			;

		// Clock the LED state machine, measure its duration
		DBG_SET();
		LedClock();
		DBG_CLR();

	}	// End - main loop
}

void GpioInit(void){
	//Enable the clock to the GPIO ports A, C
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

	//GPIO PA5 -> Green LED (active high)
	//Initialize PA5 to an output, low (green LED off)
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);

	//GPIO PA6 -> Debug pin
	//Initialize PA6 to an output, low
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);

	//GPIO PC13 <- User button (blue)
	//Initialize PC13 to an input
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_INPUT);
}

void LedClock(void)
{
	static int	LedBlinkCnt = LED_TICKS_OFF_LO;
	static int	LedState = LED_ST_OFF;

	// Clock the LED state machine
	switch(LedState)
	{
	case LED_ST_OFF:
		if (--LedBlinkCnt <= 0)
		{
			LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5);
			LedBlinkCnt = BTN_IS_PRESSED()? LED_TICKS_ON_HI : LED_TICKS_ON_LO;
			LedState = LED_ST_ON;
		}
		break;

	case LED_ST_ON:
		if (--LedBlinkCnt <= 0)
		{
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
			LedBlinkCnt = BTN_IS_PRESSED()? LED_TICKS_OFF_HI : LED_TICKS_OFF_LO;
			LedState = LED_ST_OFF;
		}
		break;
	}
}
