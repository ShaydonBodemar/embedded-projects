//
// COMP-GENG 421 - Tom Lupfer
//
// Session 23 - FBI Game, Part 1
//

#include "main.h"
#include "clock.h"
#include "dbg.h"
#include "eprintf.h"
#include "game.h"
#include "gpio.h"
#include "lcd.h"
#include "nav.h"
#include "rgb.h"
#include "uart.h"


int main(void)
{
	// Initialize hardware
	ClockInit();
	GpioInit();
	LcdInit();
	NavInit();
	UartInit();

	// Main loop
	while (TRUE)
	{
		// Wait for the 1msec tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();
		RgbClock();
		NavClock();
		GameClock();
DBG_CLR();
	} // End - main loop
}
