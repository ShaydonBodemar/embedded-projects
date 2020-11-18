//
// COMP-GENG 421 - Tom Lupfer
//
// GPIO module header file
//

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_gpio.h"


#define GPIO_PA5_CLR()		(LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5))
#define GPIO_PA5_SET()		(LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5))
#define GPIO_PA5_TOG()		(LL_GPIO_ToggleOutputPin(GPIOA, LL_GPIO_PIN_5))

#define GPIO_PA6_CLR()		(LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6))
#define GPIO_PA6_SET()		(LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_6))
#define GPIO_PA6_TOG()		(LL_GPIO_ToggleOutputPin(GPIOA, LL_GPIO_PIN_6))

#define GPIO_PC13_IS_SET()	(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13))


void GpioInit(void);

#endif	// GPIO_H_
