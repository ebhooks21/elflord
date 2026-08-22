/**
 * Game.h
 * Author: Eric HOoks
 * Purpose: Definitions for the Game structure.
 */

#ifndef GAME_H
#define GAME_H

#include "SCREEN.H"
#include "GSTATE.H"

typedef struct game_t {
	//Reference to the screen
	Screen* screen;

	//Reference to the game state
	GSTATE state;

	//Value for the menu options
	int menuOption;
} Game;

/**
 * Function to start the game.
 */
void startGame(Game* g);

/**
 * Function to destroy the game.
 */
void destroyGame(Game* g);

/**
 * Function to create the game screen.
 */
Screen* createGameScreen(int width, int height);

/**
 * Function to start the game loop.
 */
void startGameLoop(Game* g);

#endif 
