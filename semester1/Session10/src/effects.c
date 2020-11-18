//
// COMP-GENG 421 - Tom Lupfer
//
// LED effects module
//

#include "main.h"
#include "effects.h"
#include "led.h"


#define LED_UP	 0	// green LED fade up state
#define LED_DN	 1	// green LED fade down state


#define DLY_100MSEC	100	// number of ticks in 100 msec


void EffectsClock(void)
{
	static int	LedEffectsState = LED_UP;
	static int	DelayCount = DLY_100MSEC;
	static int	LedPwmSetting = LED_PWM_MIN;

	// Delay 100 msec between clocks of the state machine
	if (--DelayCount > 0)
	{
		return;
	}
	DelayCount = DLY_100MSEC;

	switch(LedEffectsState)
	{
	case LED_UP:
		LedPwmSet(LedPwmSetting++);
		if (LedPwmSetting > LED_PWM_MAX)
		{
			LedPwmSetting = LED_PWM_MAX;
			LedEffectsState = LED_DN;
		}
		break;

	case LED_DN:
		LedPwmSet(LedPwmSetting--);
		if (LedPwmSetting < LED_PWM_MIN)
		{
			LedPwmSetting = LED_PWM_MIN;
			LedEffectsState = LED_UP;
		}
		break;
	}
}
