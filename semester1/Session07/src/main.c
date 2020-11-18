//
// COMP-GENG 421 - Tom Lupfer
//
// Session 7 - UART Communications
//

#include <stdio.h>

#include "main.h"
#include "clock.h"
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

#ifndef NEVER
	UartCharWrite('U');					// Assignment 3 - Section 1
	UartCharWrite('S');
	UartCharWrite('D');
	UartCharWrite(' ');
	UartCharWrite('C');
	UartCharWrite('O');
	UartCharWrite('M');
	UartCharWrite('P');
	UartCharWrite('-');
	UartCharWrite('G');
	UartCharWrite('E');
	UartCharWrite('N');
	UartCharWrite('G');
	UartCharWrite(' ');
	UartCharWrite('4');
	UartCharWrite('2');
	UartCharWrite('1');
	UartCharWrite('\n');
#endif	// NEVER

	printf("USD COMP-GENG 421\n");		// Assignment 3 - Section 2

	printf("USD COMP-GENG %d\n", 421);	// Assignment 3 - Section 3


	// Main loop
	while(TRUE)
	{
		// Wait for tick timer
		ClockWaitForTick();

		// Clock the state machines
		DBG_SET();
		LedClock();
		printf("ABCDEFGHIJ\n");				// Assignment 3 - Section 4
		DBG_CLR();

	}	// End - main loop
}
