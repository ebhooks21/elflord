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
 * Function to render the story screen.
 */
void renderStoryScreen(Screen* s, Game* g);

#endif
