/*
 * game.c
 *
 *  Created on: Apr 26, 2020
 *      Author: Shaydon Bodemar
 *
 *      Module to handle the game itself, switching between tasks
 *      As of yet not random or timed, but does keep score
 */


#include "main.h"
#include "game.h"
#include "eprintf.h"
#include "nav.h"


#define STARTED		1
#define NOT_STARTED	0

#define SELECT		1
#define UP			2
#define DOWN		3
#define LEFT		4
#define RIGHT		5
#define PRINT_SCORE	6
#define RESET		7

#define RESET_DLY	5000


void GameClock(void){
	static int IsStarted = NOT_STARTED;
	static int TaskState = SELECT;
	static int CorrectScore = 0;
	static int IncorrectScore = 0;
	static int DelayCount = RESET_DLY;

	if(IsStarted){
		switch(TaskState){
		case SELECT:
			LcdPrintf(2, 0, "Press the SELECT button.");
			if (NavUpIsPressed())
			{
				TaskState = UP;
				IncorrectScore++;
				NavClearUpIsPressed();
			}
			if (NavDownIsPressed())
			{
				TaskState = UP;
				IncorrectScore++;
				NavClearDownIsPressed();
			}
			if (NavLeftIsPressed())
			{
				TaskState = UP;
				IncorrectScore++;
				NavClearLeftIsPressed();
			}
			if (NavRightIsPressed())
			{
				TaskState = UP;
				IncorrectScore++;
				NavClearRightIsPressed();
			}
			if (NavSelectIsPressed())
			{
				TaskState = UP;
				CorrectScore++;
				NavClearSelectIsPressed();
			}
			break;
		case UP:
			LcdPrintf(2, 0, "Press the UP button.");
			if (NavUpIsPressed())
			{
				TaskState = DOWN;
				CorrectScore++;
				NavClearUpIsPressed();
				LcdInit();
			}
			if (NavDownIsPressed())
			{
				TaskState = DOWN;
				IncorrectScore++;
				NavClearDownIsPressed();
				LcdInit();
			}
			if (NavLeftIsPressed())
			{
				TaskState = DOWN;
				IncorrectScore++;
				NavClearLeftIsPressed();
				LcdInit();
			}
			if (NavRightIsPressed())
			{
				TaskState = DOWN;
				IncorrectScore++;
				NavClearRightIsPressed();
				LcdInit();
			}
			if (NavSelectIsPressed())
			{
				TaskState = DOWN;
				IncorrectScore++;
				NavClearSelectIsPressed();
				LcdInit();
			}
			break;
		case DOWN:
			LcdPrintf(2, 0, "Press the DOWN button.");
			if (NavUpIsPressed())
			{
				TaskState = LEFT;
				IncorrectScore++;
				NavClearUpIsPressed();
				LcdInit();
			}
			if (NavDownIsPressed())
			{
				TaskState = LEFT;
				CorrectScore++;
				NavClearDownIsPressed();
				LcdInit();
			}
			if (NavLeftIsPressed())
			{
				TaskState = LEFT;
				IncorrectScore++;
				NavClearLeftIsPressed();
				LcdInit();
			}
			if (NavRightIsPressed())
			{
				TaskState = LEFT;
				IncorrectScore++;
				NavClearRightIsPressed();
				LcdInit();
			}
			if (NavSelectIsPressed())
			{
				TaskState = LEFT;
				IncorrectScore++;
				NavClearSelectIsPressed();
				LcdInit();
			}
			break;
		case LEFT:
			LcdPrintf(2, 0, "Press the LEFT button.");
			if (NavUpIsPressed())
			{
				TaskState = RIGHT;
				IncorrectScore++;
				NavClearUpIsPressed();
				LcdInit();
			}
			if (NavDownIsPressed())
			{
				TaskState = RIGHT;
				IncorrectScore++;
				NavClearDownIsPressed();
				LcdInit();
			}
			if (NavLeftIsPressed())
			{
				TaskState = RIGHT;
				CorrectScore++;
				NavClearLeftIsPressed();
				LcdInit();
			}
			if (NavRightIsPressed())
			{
				TaskState = RIGHT;
				IncorrectScore++;
				NavClearRightIsPressed();
				LcdInit();
			}
			if (NavSelectIsPressed())
			{
				TaskState = RIGHT;
				IncorrectScore++;
				NavClearSelectIsPressed();
				LcdInit();
			}
			break;
		case RIGHT:
			LcdPrintf(2, 0, "Press the RIGHT button.");
			if (NavUpIsPressed())
			{
				TaskState = PRINT_SCORE;
				IncorrectScore++;
				NavClearUpIsPressed();
				LcdInit();
			}
			if (NavDownIsPressed())
			{
				TaskState = PRINT_SCORE;
				IncorrectScore++;
				NavClearDownIsPressed();
				LcdInit();
			}
			if (NavLeftIsPressed())
			{
				TaskState = PRINT_SCORE;
				IncorrectScore++;
				NavClearLeftIsPressed();
				LcdInit();
			}
			if (NavRightIsPressed())
			{
				TaskState = PRINT_SCORE;
				CorrectScore++;
				NavClearRightIsPressed();
				LcdInit();
			}
			if (NavSelectIsPressed())
			{
				TaskState = PRINT_SCORE;
				IncorrectScore++;
				NavClearSelectIsPressed();
				LcdInit();
			}

			//print scores here
			break;
		case PRINT_SCORE:
			LcdPrintf(0, 0, "Correct Answers: %d", CorrectScore);
			LcdPrintf(2, 0, "Incorrect Answers: %d", IncorrectScore);
			TaskState = RESET;
			break;
		case RESET:
			if(--DelayCount > 0){
				return;
			}
			DelayCount = RESET_DLY;
			CorrectScore = 0;
			IncorrectScore = 0;
			TaskState = SELECT;
			IsStarted = NOT_STARTED;
			LcdInit();
			// Display the banner on the LCD
			LcdPrintf(0, 0, "COMP-GENG 421");
			LcdPrintf(1, 0, "Session 21");
			LcdPrintf(3, 0, "Nav Switch Demo");
			break;
		}
	}
	else{
		if (NavSelectIsPressed())
		{
			eprintf("S");
			NavClearSelectIsPressed();
			IsStarted = STARTED;
			LcdInit();
		}
	}
}
