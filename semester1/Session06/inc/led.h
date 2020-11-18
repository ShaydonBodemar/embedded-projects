//
// COMP-GENG 421 - Tom Lupfer
//
// LED module header file
//

#ifndef LED_H_
#define LED_H_

#include "gpio.h"


// PA5 -> Green LED (active high)
#define LED_DIS()	(GPIO_PA5_CLR())
#define LED_ENA()	(GPIO_PA5_SET())
#define LED_TOG()	(GPIO_PA5_TOG())


void LedClock(void);

#endif	// LED_H_
