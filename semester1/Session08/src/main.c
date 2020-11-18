//
// COMP-GENG 421 - Tom Lupfer
//
// Session 8 - eprintf() implementation
//

#include <stdio.h>

#include "main.h"
#include "clock.h"
#include "eprintf.h"
#include "dbg.h"
#include "gpio.h"
#include "led.h"
#include "uart.h"


int main(void)
{
	// Initialize the hardware
	ClockInit();
	GpioInit();
	UartInit();

//	eprintf("ABC\n");
//	eprintf("Hello, world! It is 2020!\n");
//	eprintf("Hello, world! It is %d!\n", 2020);

	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
		DBG_SET();

		LedClock();

		// Echo chars received on the serial port
		if (UartCharAvail())
		{
			UartCharWrite(UartCharRead());
		}

		DBG_CLR();

	}	// End - main loop
}
