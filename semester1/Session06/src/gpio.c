//
// COMP-GENG 421 - Tom Lupfer
//
// GPIO module
//

#include "main.h"
#include "gpio.h"

void GpioInit(void)
{
	// Enable the port clocks
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

	// GPIO PA5 -> Green LED (active high)
	// Initialize PA5 to an output, low (green LED off)
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);

	// GPIO PA6 -> Debug pin
	// Initialize PA6 to an output, low
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_OUTPUT);

	// GPIO PC13 <- User button (blue) - active low
	// Initialize PC13 to an input
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_INPUT);
}
