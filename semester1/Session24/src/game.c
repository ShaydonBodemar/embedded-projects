//
// COMP-GENG 421 - Tom Lupfer
//
// Game module
//

#include "main.h"
#include "accel.h"
#include "game.h"
#include "lcd.h"
#include "nav.h"


#define NAV_SEL				0x0001
#define NAV_UP				0x0002
#define NAV_DOWN			0x0004
#define NAV_LEFT			0x0008
#define NAV_RIGHT			0x0010
#define TILT_UP				0x0020
#define TILT_DOWN			0x0040
#define TILT_LEFT			0x0080
#define TILT_RIGHT			0x0100

#define NUM_ACTIONS			9		// number of actions

#define GAME_ST_INIT		0
#define GAME_ST_START		1
#define GAME_ST_PROMPT		2
#define GAME_ST_WAIT		3
#define GAME_ST_RESULTS		4
#define GAME_ST_PAUSE		5

#define RESULTS_TICKS		5000	// 5 seconds


typedef struct _ActionType
{
	char *	PromptStr;
	int		ActionBitmask;
} ActionType;


static ActionType ActionArray[NUM_ACTIONS] =
{
		{"Press Select Button  ", NAV_SEL},
		{"Press Up Button      ", NAV_UP},
		{"Press Down Button    ", NAV_DOWN},
		{"Press Left Button    ", NAV_LEFT},
		{"Press Right Button   ", NAV_RIGHT},
		{"Tilt Device Up       ", TILT_UP},
		{"Tilt Device Down     ", TILT_DOWN},
		{"Tilt Device Left     ", TILT_LEFT},
		{"Tilt Device Right    ", TILT_RIGHT}
};

static char * BlankLineStr   = "                     ";
static char * GameNameStr    = "Fraudulent BopIt Game";
static char * StartPromptStr = "Press Select to Begin";


static int ReadActions(void);
static void ClearActions(void);


void GameClock(void)
{
	static int ActionIdx;
	static int ActionsCorrect;
	static int ActionsIncorrect;
	static int GameState = GAME_ST_INIT;
	static int TickCounter;

	switch(GameState)
	{
	case GAME_ST_INIT:
		LcdPrintf(0, 0, GameNameStr);
		LcdPrintf(1, 0, BlankLineStr);
		LcdPrintf(2, 0, StartPromptStr);
		LcdPrintf(3, 0, BlankLineStr);
		ActionIdx = 0;
		ActionsCorrect = 0;
		ActionsIncorrect = 0;
		ClearActions();
		GameState = GAME_ST_START;
		break;

	case GAME_ST_START:
		if (NavSelectIsPressed())
		{
			GameState = GAME_ST_PROMPT;
		}
		break;

	case GAME_ST_PROMPT:
		LcdPrintf(0, 0, BlankLineStr);
		LcdPrintf(2, 0, "%s", ActionArray[ActionIdx].PromptStr);
		ClearActions();
		GameState = GAME_ST_WAIT;
		break;

	case GAME_ST_WAIT:
		if (!ReadActions())
		{
			break;
		}
		if (ReadActions() == ActionArray[ActionIdx].ActionBitmask)
		{
			ActionsCorrect++;
		}
		else
		{
			ActionsIncorrect++;
		}
		if (++ActionIdx >= NUM_ACTIONS)
		{
			GameState = GAME_ST_RESULTS;
		}
		else
		{
			GameState = GAME_ST_PROMPT;
		}
		break;

	case GAME_ST_RESULTS:
		LcdPrintf(0, 0, "Correct   : %2d       ", ActionsCorrect);
		LcdPrintf(2, 0, "Incorrect : %2d       ", ActionsIncorrect);
		TickCounter = RESULTS_TICKS;
		GameState = GAME_ST_PAUSE;
		break;

	case GAME_ST_PAUSE:
		if (--TickCounter <= 0)
		{
			GameState = GAME_ST_INIT;
		}
		break;
	}
}


static int ReadActions(void)
{
	return (NavSelectIsPressed() ? NAV_SEL    : 0) |
		   (NavUpIsPressed()     ? NAV_UP     : 0) |
		   (NavDownIsPressed()   ? NAV_DOWN   : 0) |
		   (NavLeftIsPressed()   ? NAV_LEFT   : 0) |
		   (NavRightIsPressed()  ? NAV_RIGHT  : 0) |
		   (AccelIsTiltedUp()    ? TILT_UP    : 0) |
		   (AccelIsTiltedDown()  ? TILT_DOWN  : 0) |
		   (AccelIsTiltedLeft()  ? TILT_LEFT  : 0) |
		   (AccelIsTiltedRight() ? TILT_RIGHT : 0);
}


static void ClearActions(void)
{
	NavClearSelectIsPressed();
	NavClearUpIsPressed();
	NavClearDownIsPressed();
	NavClearLeftIsPressed();
	NavClearRightIsPressed();
	AccelClearIsTiltedUp();
	AccelClearIsTiltedDown();
	AccelClearIsTiltedLeft();
	AccelClearIsTiltedRight();
}
