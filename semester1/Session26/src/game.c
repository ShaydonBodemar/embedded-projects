//
// COMP-GENG 421 - Shaydon Bodemar
//
// Game module
//

#include "main.h"
#include "accel.h"
#include "adc.h"
#include "game.h"
#include "lcd.h"
#include "nav.h"


#define FALSE				0
#define TRUE				1

#define NAV_SEL				0x0001
#define NAV_UP				0x0002
#define NAV_DOWN			0x0004
#define NAV_LEFT			0x0008
#define NAV_RIGHT			0x0010
#define TILT_UP				0x0020
#define TILT_DOWN			0x0040
#define TILT_LEFT			0x0080
#define TILT_RIGHT			0x0100
#define TWIST_LEFT			0x0200
#define TWIST_RIGHT			0x0400
#define SHAKE				0x0800

#define NUM_ACTIONS			12		// number of actions

#define GAME_ST_INIT		0
#define GAME_ST_START		1
#define GAME_ST_PROMPT		2
#define GAME_ST_WAIT		3
#define GAME_ST_RESULTS		4
#define GAME_ST_PAUSE		5

#define GAME_TIME			30		// seconds to be counted
#define TIMER_TICKS			1000	// 1 second
#define PROMPT_TICKS		150		// 150 ms to prompt without reading
#define RESULTS_TICKS		5000	// 5 seconds


typedef struct _ActionType
{
	char *	PromptStr;
	int		ActionBitmask;
} ActionType;


static ActionType ActionArray[NUM_ACTIONS] =
{
		{"Press Select Button  ", NAV_SEL/*, FALSE*/},
		{"Press Up Button      ", NAV_UP},
		{"Press Down Button    ", NAV_DOWN},
		{"Press Left Button    ", NAV_LEFT},
		{"Press Right Button   ", NAV_RIGHT},
		{"Tilt Device Up       ", TILT_UP},
		{"Tilt Device Down     ", TILT_DOWN},
		{"Tilt Device Left     ", TILT_LEFT},
		{"Tilt Device Right    ", TILT_RIGHT},
		{"Twist Left Knob      ", TWIST_LEFT},
		{"Twist Right Knob     ", TWIST_RIGHT},
		{"Shake Device         ", SHAKE}
};

static int ActionTicks = 0;
static int NextAction = 11;
static int HighScore = 0;

static char * BlankLineStr   = "                     ";
static char * GameNameStr    = "Fraudulent BopIt Game";
static char * StartPromptStr = "Press Select to Begin";


static int GenerateRandomAction(void);
static int ReadActions(void);
static void ClearActions(void);


void GameClock(void)
{
	static int ActionsCorrect;
	static int GameState = GAME_ST_INIT;
	static int TickCounter;
	static int SecondTicks;
	static int PromptTicks;
	static int GameTime;

	ActionTicks++;

	switch(GameState)
	{
	case GAME_ST_INIT:
		LcdPrintf(0, 0, GameNameStr);
		LcdPrintf(1, 0, BlankLineStr);
		LcdPrintf(2, 0, StartPromptStr);
		LcdPrintf(3, 0, BlankLineStr);
		ActionsCorrect = 0;
		ClearActions();
		GameState = GAME_ST_START;
		break;

	case GAME_ST_START:
		if (NavSelectIsPressed())
		{
			LcdPrintf(0, 0, BlankLineStr);
			GameState = GAME_ST_PROMPT;
			GameTime = GAME_TIME;
			SecondTicks = TIMER_TICKS;
			PromptTicks = PROMPT_TICKS;
			LcdPrintf(0, 0, "%03d                  ", GameTime);
		}
		break;

	case GAME_ST_PROMPT:
		if(--PromptTicks < 0)
		{
			PromptTicks = PROMPT_TICKS;
			NextAction = GenerateRandomAction();
			LcdPrintf(0, 18, "%03d", ActionsCorrect);
			LcdPrintf(2, 0, "%s", ActionArray[NextAction].PromptStr);
			ClearActions();
			GameState = GAME_ST_WAIT;
		}
		break;

	case GAME_ST_WAIT:
		if(--SecondTicks < 0)
		{
			SecondTicks = TIMER_TICKS;
			LcdPrintf(0, 0, "%03d", --GameTime);
			if(GameTime <= 0)
			{
				GameState = GAME_ST_RESULTS;
				break;
			}
		}
		if (!ReadActions())
		{
			break;
		}
		if (ReadActions() == ActionArray[NextAction].ActionBitmask)
		{
			ActionsCorrect++;
			GameState = GAME_ST_PROMPT;
		}
		else
		{
			GameState = GAME_ST_RESULTS;
		}
		break;

	case GAME_ST_RESULTS:
		if(ActionsCorrect > HighScore)
		{
			HighScore = ActionsCorrect;
		}
		LcdPrintf(0, 0, "Your Score : %2d       ", ActionsCorrect);
		LcdPrintf(2, 0, "High Score : %2d      ", HighScore);
		TickCounter = RESULTS_TICKS;
		GameState = GAME_ST_PAUSE;
		break;

	case GAME_ST_PAUSE:
		if (--TickCounter > 0)
		{
			break;
		}
		GameState = GAME_ST_INIT;
		break;
	}
}


static int GenerateRandomAction(void)
{
	int temp = rand() + ActionTicks;
	ActionTicks = 0;
	temp = (temp & 0xf); //should make for a number between 0 and 15

	if(temp > 11) //randomly gets this number between 0 and 11 if outside this range
	{
		temp = temp - ((rand() + ActionTicks) & 0x7) - 4;
	}

	if(temp == NextAction)
	{
		if(temp > 5)
		{
			temp -= 6;
		}
		else
		{
			temp += 6;
		}
		return temp;
	}
	else
	{
		return temp;
	}
}


static int ReadActions(void)
{
	return (NavSelectIsPressed() ? NAV_SEL     : 0) |
		   (NavUpIsPressed()     ? NAV_UP      : 0) |
		   (NavDownIsPressed()   ? NAV_DOWN    : 0) |
		   (NavLeftIsPressed()   ? NAV_LEFT    : 0) |
		   (NavRightIsPressed()  ? NAV_RIGHT   : 0) |
		   (AccelIsTiltedUp()    ? TILT_UP     : 0) |
		   (AccelIsTiltedDown()  ? TILT_DOWN   : 0) |
		   (AccelIsTiltedLeft()  ? TILT_LEFT   : 0) |
		   (AccelIsTiltedRight() ? TILT_RIGHT  : 0) |
		   (AdcIsTwistedLeft()   ? TWIST_LEFT  : 0) |
		   (AdcIsTwistedRight()  ? TWIST_RIGHT : 0) |
		   (AccelIsShaken()      ? SHAKE       : 0);
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
	AccelClearIsShaken();
	AdcClearIsTwistedLeft();
	AdcClearIsTwistedRight();
}
