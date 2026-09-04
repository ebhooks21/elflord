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
			s->currScreen = malloc(sizeof(StoryScreen));
			((StoryScreen*)s->currScreen)->page = 1;
            break;

		case INIT:
			//Init the game
			g->p = initPlayer();
			g->state = MENU;
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
