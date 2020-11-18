//
// COMP-GENG 421 - Tom Lupfer
//
// Session 21 - Navigation switch demo
//

#include "main.h"
#include "clock.h"
#include "dbg.h"
//#include "demo.h"
#include "game.h"
#include "eprintf.h"
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

	// Display the banner on the LCD
	LcdPrintf(0, 0, "COMP-GENG 421");
	LcdPrintf(1, 0, "Session 21");
	LcdPrintf(3, 0, "Nav Switch Demo");

	// Main loop
	while (TRUE)
	{
		// Wait for the 1msec tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();
		RgbClock();
		NavClock();
		//DemoClock();
		GameClock();
DBG_CLR();
	} // End - main loop
}
