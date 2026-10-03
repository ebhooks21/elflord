/**
 * Charscr.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the character screen.
 */

#include "SCREEN.H"
#include <GRX20.H>

#ifndef CHARSCR_H
#define CHARSCR_H

typedef struct {
	//Variable for the screen background
	GrContext* background;

	//Variable for the current page of the character screen
	int page;
} CharacterScreen;

/**
 * Function to initialize the character screen.
 */
CharacterScreen* initCharacterScreen(Screen* s);

/**
 * Function to destroy the character screen.
 */
void destroyCharacterScreen(CharacterScreen* c);

/**
 * Function to render the character screen.
 */
void renderCharacterScreen(CharacterScreen* c, Screen* s, Game* g);

/**
 * Function to handle character screen mouse movement.
 */
void handleCharacterScreenMouseMovement(CharacterScreen* c, Mouse* m, Game* g);

/**
 * Function to handle character screen mouse left button input.
 */
void handleCharacterScreenMouseLeftButtonInput(CharacterScreen* c, Mouse* m, Game* g);

/**
 * Function to handle character screen action.
 */
void handleCharacterScreenAction(CharacterScreen* c, Game* g);

#endif