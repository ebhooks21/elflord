/**
 * Game.c
 * Author: Eric HOoks
 * Purpose: To implement the Game functions.
 */
#include <stdlib.h>
#include <GRXKEYS.H>
#include "HEADER/GAME.H"
#include "HEADER/SCREEN.H"
#include "HEADER/GSTATE.H"

/**
 * Function to start thhe game.
 */
void startGame(Game* g) {
	g->screen = createGameScreen(320, 200);

	//Set the game state
	g->state = MENU;

	//Initialize the screen
	initScreen(g->screen);

	//Start the game loop
	startGameLoop(g);	
}

/**
 * Function to destroy the game.
 */
void destroyGame(Game* g) {
	//Destroy the screen
	destroyScreen(g->screen);

	//Release dynamic memory
	free(g->screen);
}

/**
 * Function to create a screen reference.
 */
Screen* createGameScreen(int width, int height) {
	Screen* s = malloc(sizeof(Screen));
	s->width = width;
	s->height = height;

	return s;
}

/**
 * Function to start the game loop.
 */
void startGameLoop(Game* g) {
	int running = 1;

	do {
		render(g->screen, g);

		if(GrKeyPressed != 0) {
			if(GrKeyRead() == GrKey_Escape) {
				running = 0;
			}
		}
	} while(running == 1);
}
