/**
 * Game.c
 * Author: Eric HOoks
 * Purpose: To implement the Game functions.
 */
#include <stdlib.h>
#include "HEADER/GAME.H"
#include "HEADER/SCREEN.H"
#include "HEADER/GSTATE.H"
#include "HEADER/KEYB.H"
#include "HEADER/STRYSCR.H"
#include "HEADER/GPSCR.H"

/**
 * Function to start thhe game.
 */
void startGame(Game* g) {
	g->screen = createGameScreen(320, 200);

	//Set the game state
	g->state = TITLE;

	//Preset the menu option
	g->menuOption = 0;

	//Preset the player
	g->p = NULL;

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

	//Destroy the current map
	destroyMap(g->currMap);

	//Destory the player
	destroyPlayer(g->p);

	//Release dynamic memory
	free(g->screen);
}

/**
 * Function to create a screen reference.
 */
Screen* createGameScreen(int width, int height) {
	Screen* s = malloc(sizeof *s);
	s->width = width;
	s->height = height;
	s->background = NULL;
	s->frame = NULL;

	return s;
}

/**
 * Function to define functionality that happens each time the game loop processes.
 */
 void tick(Screen* s, Game* g) {
	//Check the state and do any functionality that should be applied per that state
	switch(g->state) {
        case GAME_START_NEW:
            //Unload the background and start the game
            unloadBackground(s);

			//Clear the render count
			s->rCount = 0;

            g->state = STORY_SCREEN;

			//Create a new story screen for rendering
			s->currScreen = initStoryScreen(); 
            break;

		case INIT:
			//Init the game
			g->p = initPlayer();
			g->state = GAMEPLAY;

			//Delete the previous screen
			unloadBackground(s);
			destoryStoryScreen(s->currScreen);

			//Create a new gameplay screen for rendering
			s->currScreen = initGPScr(s);

			//Create the game map
			//Initialize the map
			g->currMap = initMap(6, 10);

			//Initialize the map data
			(g->currMap)->mapData[0][0] = 1;
			(g->currMap)->mapData[0][1] = 1;
			(g->currMap)->mapData[0][2] = 1;
			(g->currMap)->mapData[0][3] = 1;
			(g->currMap)->mapData[0][4] = 1;
			(g->currMap)->mapData[0][5] = 1;
			(g->currMap)->mapData[0][6] = 1;
			(g->currMap)->mapData[0][7] = 1;
			(g->currMap)->mapData[0][8] = 1;
			(g->currMap)->mapData[0][9] = 1;

			(g->currMap)->mapData[1][0] = 1;
			(g->currMap)->mapData[1][1] = 0;
			(g->currMap)->mapData[1][2] = 0;
			(g->currMap)->mapData[1][3] = 0;
			(g->currMap)->mapData[1][4] = 0;
			(g->currMap)->mapData[1][5] = 0;
			(g->currMap)->mapData[1][6] = 0;
			(g->currMap)->mapData[1][7] = 0;
			(g->currMap)->mapData[1][8] = 0;
			(g->currMap)->mapData[1][9] = 1;

			(g->currMap)->mapData[2][0] = 1;
			(g->currMap)->mapData[2][1] = 0;
			(g->currMap)->mapData[2][2] = 0;
			(g->currMap)->mapData[2][3] = 0;
			(g->currMap)->mapData[2][4] = 1;
			(g->currMap)->mapData[2][5] = 0;
			(g->currMap)->mapData[2][6] = 0;
			(g->currMap)->mapData[2][7] = 0;
			(g->currMap)->mapData[2][8] = 0;
			(g->currMap)->mapData[2][9] = 1;

			(g->currMap)->mapData[3][0] = 1;
			(g->currMap)->mapData[3][1] = 0;
			(g->currMap)->mapData[3][2] = 0;
			(g->currMap)->mapData[3][3] = 0;
			(g->currMap)->mapData[3][4] = 0;
			(g->currMap)->mapData[3][5] = 0;
			(g->currMap)->mapData[3][6] = 0;
			(g->currMap)->mapData[3][7] = 0;
			(g->currMap)->mapData[3][8] = 0;
			(g->currMap)->mapData[3][9] = 1;

			(g->currMap)->mapData[4][0] = 1;
			(g->currMap)->mapData[4][1] = 0;
			(g->currMap)->mapData[4][2] = 0;
			(g->currMap)->mapData[4][3] = 1;
			(g->currMap)->mapData[4][4] = 1;
			(g->currMap)->mapData[4][5] = 0;
			(g->currMap)->mapData[4][6] = 0;
			(g->currMap)->mapData[4][7] = 0;
			(g->currMap)->mapData[4][8] = 0;
			(g->currMap)->mapData[4][9] = 1;

			(g->currMap)->mapData[5][0] = 1;
			(g->currMap)->mapData[5][1] = 1;
			(g->currMap)->mapData[5][2] = 1;
			(g->currMap)->mapData[5][3] = 1;
			(g->currMap)->mapData[5][4] = 1;
			(g->currMap)->mapData[5][5] = 1;
			(g->currMap)->mapData[5][6] = 1;
			(g->currMap)->mapData[5][7] = 1;
			(g->currMap)->mapData[5][8] = 1;
			(g->currMap)->mapData[5][9] = 1;
			break;

        default:
            break;
    }
 }

/**
 * Function to start the game loop.
 */
void startGameLoop(Game* g) {
	int running = 1;

	do {
		//Process the tick, which runs each game loop
		tick(g->screen, g);

		//Render the game screen
		render(g->screen, g);

		//Check for keyboard input
		processKeyInput(g);
	} while(g->state != EXIT_GAME);
}
