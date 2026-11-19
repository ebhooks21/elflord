/**
 * Sucesssr.h
 * Author: Eric Hooks
 * Purpose: To handle rendering for the success screen.
 */

#include "SCREEN.H"
#include <GRX20.H>

#ifndef SUCESSSR_H
#define SUCESSSR_H

typedef struct {
	//Variable for the screen background
	GrContext* background;

	//Variable for the success screen page
	int page;
} SuccessScreen;

/**
 * Function to initialize the success screen.
 */
SuccessScreen* initSuccessScreen(Screen* s);

/**
 * Function to destroy the success screen.
 */
void destroySuccessScreen(SuccessScreen* s);

/**
 * Function to render the success screen.
 */
void renderSuccessScreen(SuccessScreen* ss, Screen* s, Game* g);

/**
 * Function to handle success screen mouse left button input.
 */
void handleSuccessScreenMouseLeftButtonInput(SuccessScreen* s, Mouse* m, Game* g);

/**
 * Function to handle success screen action.
 */
void handleSuccessScreenAction(SuccessScreen* s, Game* g);

#endif
