//
// COMP-GENG 421 - Tom Lupfer
//
// Session 17 - LED PWM effects
//

#include "main.h"
#include "clock.h"
#include "dbg.h"
#include "effects.h"
#include "eprintf.h"
#include "gpio.h"
#include "led.h"
#include "rgb.h"
#include "uart.h"


int main(void)
{
	// Initialize hardware
	ClockInit();
	GpioInit();
	UartInit();

	// Main loop
	while (TRUE)
	{
		// Wait for the 1msec tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();
		LedClock();
		RgbClock();
		EffectsClock();

		// Echo chars received on the serial port
		if (UartCharAvail())
		{
			UartCharWrite(UartCharRead());
		}
DBG_CLR();
	} // End - main loop
}
