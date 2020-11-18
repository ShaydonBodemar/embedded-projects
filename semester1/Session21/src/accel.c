//
// COMP-GENG 421 - Tom Lupfer
//
// Accelerometer module
//

#include "main.h"
#include "accel.h"
#include "i2c.h"


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
