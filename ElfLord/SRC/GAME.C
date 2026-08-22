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
	g->state = TITLE;

	//Preset the menu option
	g->menuOption = 0;

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
	s->background = NULL;

	return s;
}

/**
 * Function to start the game loop.
 */
void startGameLoop(Game* g) {
	int running = 1;
	GrKeyType key;

	do {
		render(g->screen, g);

		if(GrKeyPressed != 0) {
			key = GrKeyRead();

			switch(g->state) {
				case TITLE:
					if(key == GrKey_Return) {
						switch(g->menuOption) {
							case 0:
								g->state = MENU;
								break;
							
							case 2:
								running = 0;
								break;
						}
					}

					else if((key == GrKey_Up) && (g->menuOption > 0)) {
						g->menuOption--;
					}

					else if((key == GrKey_Down) && (g->menuOption < 2)) {
						g->menuOption++;
					}
					break;

				default:
					if(key == GrKey_Escape) {
						running = 0;
					}
					break;
			}	
		}
	} while(running == 1);
}
