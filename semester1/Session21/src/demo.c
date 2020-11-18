//
// COMP-GENG 421 - Tom Lupfer
//
// Navigation switch demo module
//


#include "main.h"
#include "demo.h"
#include "i2c.h"
#include "lcd.h"
#include "nav.h"


#define REFRESH_TICKS	100


void DemoClock(void)
{
	static int TickCount = REFRESH_TICKS;

	UInt8 RcvBuf[3];

	if (--TickCount <= 0)
	{
		TickCount = REFRESH_TICKS;
		I2cRead(0x98, 0x00, 0x03, RcvBuf);

		LcdPrintf(3, 0, "X: %3d Y: %3d Z: %3d",
			(int) ((RcvBuf[0] << 26) >> 26),
			(int) ((RcvBuf[1] << 26) >> 26),
			(int) ((RcvBuf[2] << 26) >> 26));
	}
}
