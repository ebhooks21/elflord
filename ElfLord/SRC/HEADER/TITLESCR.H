/**
 * Titlescr.h
 * Author: Eric Hooks
 * Purpose: To handle rendering for the title screen.
 */

#include <GRX20.H>
#include "SCREEN.H"

#ifndef TITLESCR_H
#define TITLESCR_H

typedef struct {
	//Variable for the new game text
	char* newGameText;

	//Variable for the continue game text
	char* continueGameText;

	//Variable for the return to dos text
	char* returnToDosText;

	//Variable for the title screen background
	GrContext* background;
} TitleScreen;

/**
 * Function to initialize the title screen.
 */
TitleScreen* initTitleScreen(Screen* s);

/**
 * Function to destory the title screen.
 */
void destoryTitleScreen(TitleScreen* t);

/**
 * Function to render the title screen.
 */
void renderTitleScreen(TitleScreen* t, Screen* s, Game* g, int menuOption);

#endif