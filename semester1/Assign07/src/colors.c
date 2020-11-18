/*
 *	This module will change the colors of the RGB LED, modifying on, in total, 14 states.
 *
 *  Created on: Apr 14, 2020
 *      Author: Shaydon Bodemar
 *       Class: COMP/GENG 421
 */

#include "main.h"
#include "colors.h"
#include "rgb.h"

#define RED_UP      0
#define RED_DN      1
#define GRN_UP      2
#define GRN_DN      3
#define BLU_UP      4
#define BLU_DN      5
#define RED_GRN_UP  6
#define RED_GRN_DN  7
#define GRN_BLU_UP  8
#define GRN_BLU_DN  9
#define BLU_RED_UP  10
#define BLU_RED_DN  11
#define RGB_UP      12
#define RGB_DN      13




#define DLY_100MSEC	100	// number of ticks in 100 msec


void ColorsClock(void){
	static int RgbColorsState = RED_UP;
	static int DelayCount = DLY_100MSEC;

	static int RedPwmSetting = RGB_RED_PWM_MIN;
	static int GreenPwmSetting = RGB_GRN_PWM_MIN;
	static int BluePwmSetting = RGB_BLU_PWM_MIN;


	// Delay 100 msec between clocks of the state machine
	if (--DelayCount > 0)
	{
		return;
	}
	DelayCount = DLY_100MSEC;


	switch(RgbColorsState){
	case RED_UP:
		RgbRedPwmSet(RedPwmSetting++);
		if (RedPwmSetting > RGB_RED_PWM_MAX){
			RedPwmSetting = RGB_RED_PWM_MAX;
			RgbColorsState = RED_DN;
		}
		break;

	case RED_DN:
		RgbRedPwmSet(RedPwmSetting--);
		if (RedPwmSetting < RGB_RED_PWM_MIN){
			RedPwmSetting = RGB_RED_PWM_MIN;
			RgbColorsState = RED_UP;
		}
		break;

	case GRN_UP:
		LedPwmSet(GreenPwmSetting++);
		break;

	case GRN_DN:
		LedPwmSet(GreenPwmSetting--);
		break;

	case BLU_UP:
		LedPwmSet(BluePwmSetting++);
		break;

	case BLU_DN:
		LedPwmSet(BluePwmSetting--);
		break;

	case RED_GRN_UP:
		LedPwmSet(RedPwmSetting++);
		LedPwmSet(GreenPwmSetting++);
		break;

	case RED_GRN_DN:
		LedPwmSet(RedPwmSetting--);
		LedPwmSet(GreenPwmSetting--);
		break;

	case GRN_BLU_UP:
		LedPwmSet(GreenPwmSetting++);
		LedPwmSet(BluePwmSetting++);
		break;

	case GRN_BLU_DN:
		LedPwmSet(GreenPwmSetting--);
		LedPwmSet(BluePwmSetting--);
		break;

	case BLU_RED_UP:
		LedPwmSet(BluePwmSetting++);
		LedPwmSet(RedPwmSetting++);
		break;

	case BLU_RED_DN:
		LedPwmSet(BluePwmSetting--);
		LedPwmSet(RedPwmSetting--);
		break;

	case RGB_UP:
		LedPwmSet(RedPwmSetting++);
		LedPwmSet(GreenPwmSetting++);
		break;

	case RGB_DN:
		LedPwmSet(RedPwmSetting--);
		LedPwmSet(GreenPwmSetting--);
		break;
	}
}
