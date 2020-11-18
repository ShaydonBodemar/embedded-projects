//
// COMP-GENG 421 - Shaydon Bodemar
//
// Accelerometer reading module
//

#include "main.h"
#include "accel.h"
#include "i2c.h"


#define REFRESH_TICKS	100

static Bool	ForwardTilt = FALSE;		// forward tilt?
static Bool	BackwardTilt = FALSE;		// backwards tilt?
static Bool	LeftTilt = FALSE;			// left tilt?
static Bool	RightTilt = FALSE;			// right tilt?


void AccelInit(void)
{
	UInt8 XmtBuf[1];

	// Clear all of the control registers to their default values
	XmtBuf[0] = 0x00;
	I2cWrite(0x98, 0x07, 0x01, XmtBuf);	// clear TON bit to get out of test mode
	I2cWrite(0x98, 0x06, 0x01, XmtBuf);
	I2cWrite(0x98, 0x08, 0x01, XmtBuf);
	I2cWrite(0x98, 0x09, 0x01, XmtBuf);
	I2cWrite(0x98, 0x0A, 0x01, XmtBuf);

	// Enable the active mode
	XmtBuf[0] = 0x01;
	I2cWrite(0x98, 0x07, 0x01, XmtBuf);
}

void AccelClock(void)
{
	static int TickCount = REFRESH_TICKS;

	UInt8 RcvBuf[3];

	if (--TickCount <= 0)
	{
		TickCount = REFRESH_TICKS;
		I2cRead(0x98, 0x00, 0x03, RcvBuf);

		int X_Val = (int) ((RcvBuf[0] << 26) >> 26);
		int Y_Val = (int) ((RcvBuf[1] << 26) >> 26);
		int Z_Val = (int) ((RcvBuf[2] << 26) >> 26); //will late be useful for shaking

		//Value of 10 used as a conservative sin(30)*22
		if(X_Val >= 10)
		{
			ForwardTilt = TRUE;
		}
		if(X_Val <= -10)
		{
			BackwardTilt = TRUE;
		}
		if(Y_Val >= 10)
		{
			LeftTilt = TRUE;
		}
		if(Y_Val <= -10)
		{
			RightTilt = TRUE;
		}
	}
}

Bool TiltedForward(void)
{
	return ForwardTilt;
}

void ClearTiltedForward(void)
{
	ForwardTilt = FALSE;
}

Bool TiltedBackward(void)
{
	return BackwardTilt;
}

void ClearTiltedBackward(void)
{
	BackwardTilt = FALSE;
}

Bool TiltedLeft(void)
{
	return LeftTilt;
}

void ClearTiltedLeft(void)
{
	LeftTilt = FALSE;
}

Bool TiltedRight(void)
{
	return RightTilt;
}

void ClearTiltedRight(void)
{
	RightTilt = FALSE;
}
