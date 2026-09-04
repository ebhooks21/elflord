/**
 * Game.h
 * Author: Eric HOoks
 * Purpose: Definitions for the Game structure.
 */

#ifndef GAME_H
#define GAME_H

#include "SCREEN.H"
#include "GSTATE.H"
#include "PLAYER.H"

typedef struct game_t {
	//Reference to the screen
	Screen* screen;

	//Reference to the game state
	GSTATE state;

	//Value for the menu options
	int menuOption;

	//Variable for the player
	Player* p;
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
 * Function to define functionality that happens each time the game loop processes.
 */
 void tick(Screen* s, Game* g);

/**
 * Function to start the game loop.
 */
void startGameLoop(Game* g);

#endif 
