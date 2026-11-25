/**
 * Dscreen.h
 * Author: Eric Hooks
 * Purpose: To handle rendering for the death screen.
 */

#include "SCREEN.H"
#include <GRX20.H>

#ifndef DSCREEN_H
#define DSCREEN_H

typedef struct {
	//Variable for the screen background
	GrContext* background;
} DeathScreen;

/**
 * Function to initialize the death screen.
 */
DeathScreen* initDeathScreen(Screen* s);

/**
 * Function to destroy the death screen.
 */
void destroyDeathScreen(DeathScreen* s);

/**
 * Function to render the death screen.
 */
void renderDeathScreen(DeathScreen* ss, Screen* s, Game* g);

/**
 * Function to handle death screen mouse left button input.
 */
void handleDeathScreenMouseLeftButtonInput(DeathScreen* s, Mouse* m, Game* g);

/**
 * Function to handle death screen action.
 */
void handleDeathScreenAction(DeathScreen* s, Game* g);

#endif
