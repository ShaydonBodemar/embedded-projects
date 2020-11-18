//
// COMP-GENG 421 - Tom Lupfer
//
// Navigation switch demo module
//


#include "main.h"
#include "demo.h"
#include "eprintf.h"
#include "nav.h"


void DemoClock(void)
{
	if (NavUpIsPressed())
	{
		eprintf("U");
		NavClearUpIsPressed();
	}
	if (NavDownIsPressed())
	{
		eprintf("D");
		NavClearDownIsPressed();
	}
	if (NavLeftIsPressed())
	{
		eprintf("L");
		NavClearLeftIsPressed();
	}
	if (NavRightIsPressed())
	{
		eprintf("R");
		NavClearRightIsPressed();
	}
	if (NavSelectIsPressed())
	{
		eprintf("S");
		NavClearSelectIsPressed();
	}
}
