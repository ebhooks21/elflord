/**
 * Ccscr.h 
 * Author: Eric Hooks, 2026
 * Purpose: To define the close confirmation screen.
 */

#include "GIMAGE.H"
#include "SCREEN.H"
#include "GAME.H"

#ifndef CCSCR_H
#define CCSCR_H

typedef struct {
	//Variable for the screen background
	GameImage* background;
} CloseConfirmScreen;

/**
 * Function to initialize the close confirmation screen.
 */
CloseConfirmScreen* initCloseConfirmScreen(Screen* s);

/**
 * Function to destroy the close confirmation screen.
 */
void destroyCloseConfirmationScreen(CloseConfirmScreen* c);

/**
 * Function to render the close confirmation screen.
 */
void renderCloseConfirmationScreen(CloseConfirmScreen* c, Screen* s, Game* g);

#endif