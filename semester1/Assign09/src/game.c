//
// COMP-GENG 421 - Shaydon Bodemar
//
// Game module
//

#include "main.h"
#include "game.h"
#include "lcd.h"
#include "nav.h"


#define NAV_SEL				0x01
#define NAV_UP				0x02
#define NAV_DOWN			0x04
#define NAV_LEFT			0x08
#define NAV_RIGHT			0x10
#define TILT_FWD			0x20
#define TILT_BWD			0x40
#define TILT_LEFT			0x80
#define TILT_RIGHT			0x100

#define GAME_ST_INIT		0
#define GAME_ST_START		1
#define GAME_ST_NAV_SEL		2
#define GAME_ST_NAV_UP		3
#define GAME_ST_NAV_DOWN	4
#define GAME_ST_NAV_LEFT	5
#define GAME_ST_NAV_RIGHT	6
#define GAME_TILT_FORWARD	7
#define GAME_TILT_BACKWARD	8
#define GAME_TILT_LEFT		9
#define GAME_TILT_RIGHT		10
#define GAME_ST_RESULTS		11

#define RESULTS_TICKS		5000	// 5 seconds


static int ReadAllInputs(void);
static void ClearAllInputs(void);


void GameClock(void)
{
	static int ActionsCorrect;
	static int ActionsIncorrect;
	static int GameState = GAME_ST_INIT;
	static int TickCounter;

	switch(GameState)
	{
	case GAME_ST_INIT:
		LcdPrintf(0, 0, "Fraudulent BopIt Game");
		LcdPrintf(1, 0, "                     ");
		LcdPrintf(2, 0, "Press Select to Begin");
		LcdPrintf(3, 0, "                     ");
		ActionsCorrect = 0;
		ActionsIncorrect = 0;
		ClearAllInputs();
		GameState = GAME_ST_START;
		break;

	case GAME_ST_START:
		if (NavSelectIsPressed())
		{
			LcdPrintf(0, 0, "                     ");
			LcdPrintf(2, 0, "Press Select Button  ");
			ClearAllInputs();
			GameState = GAME_ST_NAV_SEL;
		}
		break;

	case GAME_ST_NAV_SEL:
		if (!ReadAllInputs())
		{
			break;
		}
		if (NavSelectIsPressed())
		{
			ActionsCorrect++;
		}
		else
		{
			ActionsIncorrect++;
		}
		LcdPrintf(2, 0, "Press Up Button      ");
		ClearAllInputs();
		GameState = GAME_ST_NAV_UP;
		break;

	case GAME_ST_NAV_UP:
		if (!ReadAllInputs())
		{
			break;
		}
		if (NavUpIsPressed())
		{
			ActionsCorrect++;
		}
		else
		{
			ActionsIncorrect++;
		}
		LcdPrintf(2, 0, "Press Down Button    ");
		ClearAllInputs();
		GameState = GAME_ST_NAV_DOWN;
		break;

	case GAME_ST_NAV_DOWN:
		if (!ReadAllInputs())
		{
			break;
		}
		if (NavDownIsPressed())
		{
			ActionsCorrect++;
		}
		else
		{
			ActionsIncorrect++;
		}
		LcdPrintf(2, 0, "Press Left Button    ");
		ClearAllInputs();
		GameState = GAME_ST_NAV_LEFT;
		break;

	case GAME_ST_NAV_LEFT:
		if (!ReadAllInputs())
		{
			break;
		}
		if (NavLeftIsPressed())
		{
			ActionsCorrect++;
		}
		else
		{
			ActionsIncorrect++;
		}
		LcdPrintf(2, 0, "Press Right Button   ");
		ClearAllInputs();
		GameState = GAME_ST_NAV_RIGHT;
		break;

	case GAME_ST_NAV_RIGHT:
		if (!ReadAllInputs())
		{
			break;
		}
		if (NavRightIsPressed())
		{
			ActionsCorrect++;
		}
		else
		{
			ActionsIncorrect++;
		}
		LcdPrintf(2, 0, "Tilt game forward    ");
		ClearAllInputs();
		GameState = GAME_TILT_FORWARD;
		break;

	case GAME_TILT_FORWARD:
		if (!ReadAllInputs())
		{
			break;
		}
		if (TiltedForward())
		{
			ActionsCorrect++;
		}
		else
		{
			ActionsIncorrect++;
		}
		LcdPrintf(2, 0, "Tilt game backward   ");
		ClearAllInputs();
		GameState = GAME_TILT_BACKWARD;
		break;

	case GAME_TILT_BACKWARD:
		if (!ReadAllInputs())
		{
			break;
		}
		if (TiltedBackward())
		{
			ActionsCorrect++;
		}
		else
		{
			ActionsIncorrect++;
		}
		LcdPrintf(2, 0, "Tilt game to left    ");
		ClearAllInputs();
		GameState = GAME_TILT_LEFT;
		break;

	case GAME_TILT_LEFT:
		if (!ReadAllInputs())
		{
			break;
		}
		if (TiltedLeft())
		{
			ActionsCorrect++;
		}
		else
		{
			ActionsIncorrect++;
		}
		LcdPrintf(2, 0, "Tilt game to right   ");
		ClearAllInputs();
		GameState = GAME_TILT_RIGHT;
		break;

	case GAME_TILT_RIGHT:
		if (!ReadAllInputs())
		{
			break;
		}
		if (TiltedRight())
		{
			ActionsCorrect++;
		}
		else
		{
			ActionsIncorrect++;
		}
		LcdPrintf(0, 0, "Correct   : %2d       ", ActionsCorrect);
		LcdPrintf(2, 0, "Incorrect : %2d       ", ActionsIncorrect);
		TickCounter = RESULTS_TICKS;
		GameState = GAME_ST_RESULTS;
		break;

	case GAME_ST_RESULTS:
		if (--TickCounter <= 0)
		{
			GameState = GAME_ST_INIT;
		}
		break;
	}
}


static int ReadAllInputs(void)
{
	return (NavSelectIsPressed() ? NAV_SEL   : 0) |
		   (NavUpIsPressed()     ? NAV_UP    : 0) |
		   (NavDownIsPressed()   ? NAV_DOWN  : 0) |
		   (NavLeftIsPressed()   ? NAV_LEFT  : 0) |
		   (NavRightIsPressed()  ? NAV_RIGHT : 0) |
		   (TiltedForward()   	 ? TILT_FWD  : 0) |
		   (TiltedBackward() 	 ? TILT_BWD  : 0) |
		   (TiltedLeft()   	 	 ? TILT_LEFT : 0) |
		   (TiltedRight()    	 ? TILT_RIGHT: 0);
}


static void ClearAllInputs(void)
{
	NavClearSelectIsPressed();
	NavClearUpIsPressed();
	NavClearDownIsPressed();
	NavClearLeftIsPressed();
	NavClearRightIsPressed();
	ClearTiltedForward();
	ClearTiltedBackward();
	ClearTiltedRight();
	ClearTiltedLeft();
}
