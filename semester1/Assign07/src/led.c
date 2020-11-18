//
// COMP-GENG 421 - Tom Lupfer
//
// LED module
//

#include "main.h"
#include "led.h"


#define LED_ST_OFF		0
#define LED_ST_ON		1


static int	LedPwmSetting = 0;


void LedClock(void)
{
	static int	LedState = LED_ST_OFF;
	static int	LedPwmCount = 0;

	LedPwmCount++;
	switch(LedState)
	{
	case LED_ST_OFF:
		if (LedPwmCount == LED_PWM_MAX)
		{
			LedPwmCount = 0;
			if (LedPwmSetting != 0)
			{
				LED_ENA();
				LedState = LED_ST_ON;
				break;
			}
		}
		break;

	case LED_ST_ON:
		if (LedPwmCount >= LedPwmSetting)
		{
			if (LedPwmSetting == LED_PWM_MAX)
			{
				LedPwmCount = 0;
			}
			else
			{
				LED_DIS();
				LedState = LED_ST_OFF;
				break;
			}
		}
		break;
	}
}


void LedPwmSet(int PwmSetting)
{
	if (PwmSetting == 0)
	{
		LedPwmSetting = 0;
		return;
	}
	if (PwmSetting < LED_PWM_MIN)
	{
		PwmSetting = LED_PWM_MIN;
	}
	if (PwmSetting > LED_PWM_MAX)
	{
		PwmSetting = LED_PWM_MAX;
	}
	LedPwmSetting = PwmSetting;
}


int LedPwmGet(void)
{
	return LedPwmSetting;
}
