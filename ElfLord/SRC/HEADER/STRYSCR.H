/**
 * Stryscr.h
 * Author: Eric Hooks
 * Purpose: To handle rendering for the story screen.
 */

#include "SCREEN.H"

#ifndef STRYSCR_H
#define STRYSCR_H

typedef struct {
	//Variable for the story screen page
	int page;
} StoryScreen;

/**
 * Function to initialize the story screen.
 */
StoryScreen* initStoryScreen();

/**
 * Function to destory the story screen.
 */
void destoryStoryScreen(StoryScreen* s);

/**
 * Function to render the story screen.
 */
void renderStoryScreen(Screen* s, Game* g);

#endif
