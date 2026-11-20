/**
 * Helpscr.h
 * Author: Eric Hooks
 * Purpose: To handle rendering for the help screen.
 */

#include "SCREEN.H"
#include <GRX20.H>

#ifndef HELPSCR_H
#define HELPSCR_H

typedef struct {
	//Variable for the screen background
	GrContext* background;

	//Variable for the help screen page
	int page;
} HelpScreen;

/**
 * Function to initialize the help screen.
 */
HelpScreen* initHelpScreen(Screen* s);

/**
 * Function to destroy the help screen.
 */
void destroyHelpScreen(HelpScreen* s);

/**
 * Function to render the help screen.
 */
void renderHelpScreen(HelpScreen* ss, Screen* s, Game* g);

/**
 * Function to handle help screen mouse left button input.
 */
void handleHelpScreenMouseLeftButtonInput(HelpScreen* s, Mouse* m, Game* g);

/**
 * Function to handle help screen action.
 */
void handleHelpScreenAction(HelpScreen* s, Game* g);

#endif
