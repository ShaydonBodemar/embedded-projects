//
// COMP-GENG 421 - Shaydon Bodemar
//
// Session 26 - FBI Game with Shake & Twist Demo Code
//

#include "main.h"
#include "accel.h"
#include "adc.h"
#include "clock.h"
#include "dbg.h"
#include "eprintf.h"
#include "game.h"
#include "gpio.h"
#include "i2c.h"
#include "lcd.h"
#include "nav.h"
#include "rgb.h"
#include "uart.h"


int main(void)
{
	// Initialize hardware
	ClockInit();
	GpioInit();
	I2cInit();

	// Initialize peripherals
	UartInit();	// done first for debugging
	AccelInit();
	AdcInit();
	LcdInit();
	NavInit();

	// Main loop
	while (TRUE)
	{
		// Wait for the 1msec tick timer
		ClockWaitForTick();

		// Clock the state machines
DBG_SET();
		// Peripheral state machines
		AccelClock();
		AdcClock();
		NavClock();
		RgbClock();

		// Application state machines
		GameClock();
DBG_CLR();
	} // End - main loop
}
