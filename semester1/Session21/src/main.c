//
// COMP-GENG 421 - Tom Lupfer
//
// Session 21 - Accelerometer demo
//

#include "main.h"
#include "accel.h"
#include "clock.h"
#include "dbg.h"
#include "demo.h"
#include "eprintf.h"
#include "gpio.h"
#include "i2c.h"
#include "lcd.h"
#include "nav.h"
#include "rgb.h"
#include "uart.h"


int main(void)
{
	// Initialize MCU hardware
	ClockInit();
	GpioInit();
	I2cInit();
	UartInit();

	// Initialize external peripherals
	AccelInit();
	LcdInit();
	NavInit();

	// Display the banner on the LCD
	LcdPrintf(0, 0, "COMP-GENG 421");
	LcdPrintf(1, 0, "Accelerometer Demo");

	// Main loop
	while (TRUE)
	{
		// Wait for the 1msec tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();
		RgbClock();
		NavClock();
		DemoClock();
DBG_CLR();
	} // End - main loop
}
