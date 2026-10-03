/**
 * Stryscr.h
 * Author: Eric Hooks
 * Purpose: To handle rendering for the story screen.
 */

#include "SCREEN.H"
#include <GRX20.H>

#ifndef STRYSCR_H
#define STRYSCR_H

typedef struct {
	//Variable for the screen background
	GrContext* background;

	//Variable for the story screen page
	int page;
} StoryScreen;

/**
 * Function to initialize the story screen.
 */
StoryScreen* initStoryScreen(Screen* s);

/**
 * Function to destory the story screen.
 */
void destoryStoryScreen(StoryScreen* s);

/**
 * Function to render the story screen.
 */
void renderStoryScreen(StoryScreen* ss, Screen* s, Game* g);

/**
 * Function to handle story screen mouse left button input.
 */
void handleStoryScreenMouseLeftButtonInput(StoryScreen* s, Mouse* m, Game* g);

/**
 * Function to handle story screen action.
 */
void handleStoryScreenAction(StoryScreen* s, Game* g);

#endif
