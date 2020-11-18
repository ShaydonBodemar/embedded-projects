//
// COMP-GENG 421 - Tom Lupfer
//
// LED module header file
//

#ifndef LED_H_
#define LED_H_

#include "gpio.h"


#define LED_DIS()		(GPIO_PA5_CLR())
#define LED_ENA()		(GPIO_PA5_SET())
#define LED_TOG()		(GPIO_PA5_TOG())

#define LED_PWM_MIN		 0
#define LED_PWM_MAX		10


void	LedClock(void);
void	LedPwmSet(int PwmSetting);
int		LedPwmGet(void);

#endif	// LED_H_
