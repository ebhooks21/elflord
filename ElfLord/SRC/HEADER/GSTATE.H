/**
* GState.h
* Author: Eric Hooks
* Purpose: To define the GameState enum.
*/

#ifndef GSTATE_H
#define GSTATE_H

typedef enum {
	TITLE,
	GAME_START_NEW,
	GAME_START_CONTINUE,
	STORY_SCREEN,
	MENU,
	MOVEMENT,
	EXIT_PROMPT,
	EXIT_GAME
} GSTATE;

#endif
