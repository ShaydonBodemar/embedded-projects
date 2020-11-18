//
// COMP-GENG 421 - Tom Lupfer
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

#define GAME_ST_INIT		0
#define GAME_ST_START		1
#define GAME_ST_NAV_SEL		2
#define GAME_ST_NAV_UP		3
#define GAME_ST_NAV_DOWN	4
#define GAME_ST_NAV_LEFT	5
#define GAME_ST_NAV_RIGHT	6
#define GAME_ST_RESULTS		7

#define RESULTS_TICKS		5000	// 5 seconds


static int ReadAllNavButtons(void);
static void ClearAllNavButtons(void);


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
		ClearAllNavButtons();
		GameState = GAME_ST_START;
		break;

	case GAME_ST_START:
		if (NavSelectIsPressed())
		{
			LcdPrintf(0, 0, "                     ");
			LcdPrintf(2, 0, "Press Select Button  ");
			ClearAllNavButtons();
			GameState = GAME_ST_NAV_SEL;
		}
		break;

	case GAME_ST_NAV_SEL:
		if (!ReadAllNavButtons())
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
		ClearAllNavButtons();
		GameState = GAME_ST_NAV_UP;
		break;

	case GAME_ST_NAV_UP:
		if (!ReadAllNavButtons())
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
		ClearAllNavButtons();
		GameState = GAME_ST_NAV_DOWN;
		break;

	case GAME_ST_NAV_DOWN:
		if (!ReadAllNavButtons())
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
		ClearAllNavButtons();
		GameState = GAME_ST_NAV_LEFT;
		break;

	case GAME_ST_NAV_LEFT:
		if (!ReadAllNavButtons())
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
		ClearAllNavButtons();
		GameState = GAME_ST_NAV_RIGHT;
		break;

	case GAME_ST_NAV_RIGHT:
		if (!ReadAllNavButtons())
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


static int ReadAllNavButtons(void)
{
	return (NavSelectIsPressed() ? NAV_SEL   : 0) |
		   (NavUpIsPressed()     ? NAV_UP    : 0) |
		   (NavDownIsPressed()   ? NAV_DOWN  : 0) |
		   (NavLeftIsPressed()   ? NAV_LEFT  : 0) |
		   (NavRightIsPressed()  ? NAV_RIGHT : 0);
}


static void ClearAllNavButtons(void)
{
	NavClearSelectIsPressed();
	NavClearUpIsPressed();
	NavClearDownIsPressed();
	NavClearLeftIsPressed();
	NavClearRightIsPressed();
}
