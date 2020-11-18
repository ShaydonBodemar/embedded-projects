//
// COMP-GENG 421 - Tom Lupfer
//
// LED module
//

#include "main.h"
#include "btn.h"
#include "led.h"


#define LED_ST_OFF			0
#define LED_ST_ON			1

#define LED_TICKS_OFF		400
#define LED_TICKS_ON		100


void LedClock(void)
{
	static int		LedBlinkCnt = LED_TICKS_OFF;
	static int		LedState = LED_ST_OFF;

	volatile int	JitterCnt;

	// Clock the LED state machine
	// Add jitter when the button is pressed
	switch(LedState)
	{
	case LED_ST_OFF:
		if (--LedBlinkCnt <= 0)
		{
			LED_ENA();
			LedBlinkCnt = LED_TICKS_ON;
			LedState = LED_ST_ON;
		}
		break;

	case LED_ST_ON:
		if (BTN_IS_PRESSED())
		{
			for (JitterCnt = 0; JitterCnt < 500; JitterCnt++)
				;
		}
		if (--LedBlinkCnt <= 0)
		{
			LED_DIS();
			LedBlinkCnt = LED_TICKS_OFF;
			LedState = LED_ST_OFF;
		}
		break;
	}
}
