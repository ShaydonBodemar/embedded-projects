//
// COMP-GENG 421 - Tom Lupfer
//
// Session 6 - Hardware Tick Timer
//

#include "main.h"
#include "clock.h"
#include "dbg.h"
#include "gpio.h"
#include "led.h"


int main(void)
{
	// Initialize the hardware
	ClockInit();
	GpioInit();

	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
		DBG_SET();
		LedClock();
		DBG_CLR();

	}	// End - main loop
}
