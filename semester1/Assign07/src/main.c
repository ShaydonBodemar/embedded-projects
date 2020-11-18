//
// COMP-GENG 421 - Tom Lupfer
//
// Session 18 - LCD driver
//

#include "main.h"
#include "clock.h"
#include "dbg.h"
#include "colors.h"
#include "effects.h"
#include "eprintf.h"
#include "gpio.h"
#include "lcd.h"
#include "led.h"
#include "rgb.h"
#include "uart.h"


int main(void)
{
	// Initialize hardware
	ClockInit();
	GpioInit();
	LcdInit();
	UartInit();

	// Set RGB LED to magenta at full brightness
	//RgbRedPwmSet(RGB_RED_PWM_MAX);
	//RgbBluPwmSet(RGB_BLU_PWM_MAX);

	// Display the banner on the LCD
	LcdPrintf(0, 0, "COMP-GENG 421");
	LcdPrintf(1, 0, "Session 18");
	LcdPrintf(3, 0, "LCD text display");

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
		ColorsClock();

		// Echo chars received on the serial port
		if (UartCharAvail())
		{
			UartCharWrite(UartCharRead());
		}
DBG_CLR();
	} // End - main loop
}
