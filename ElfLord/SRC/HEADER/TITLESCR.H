/**
 * Titlescr.h
 * Author: Eric Hooks
 * Purpose: To handle rendering for the title screen.
 */

#include <GRX20.H>
#include "SCREEN.H"
#include "MENUOPT.H"

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

	//Variable for the selected menu option
	int menuOption;

	//Variable for the menu options
	MenuOption* mOpt[3];
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
void renderTitleScreen(TitleScreen* t, Screen* s, Game* g);

/**
 * Function to create the title screen menu options.
 */
void createTitleScreenMenuOptions(TitleScreen* t, Screen* s);

/**
 * Fucntion to handle title screen mouse movement.
 */
void handleTitleScreenMouseMovement(TitleScreen* t, Mouse* m, Game* g);

/**
 * Fucntion to handle title screen mouse left button input.
 */
void handleTitleScreenMouseLeftButtonInput(TitleScreen* t, Mouse* m, Game* g);

/**
 * Function to handle title screen action.
 */
void handleTitleScreenAction(TitleScreen* t, Game* g);

#endif