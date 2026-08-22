/**
 * Screen.h
 * Author: Eric HOoks
 * Purpose: Definitions for the Screen functions.
 */

#include <GRX20.H>

#ifndef SCREEN_H
#define SCREEN_H

//Forward declare the game structure
typedef struct game_t Game;

//Define the Screen
typedef struct screen_t {
	//Width of the screen
	int width;

	//Height of the screen
	int height;

	//Context for the entire screen background
	GrContext* background;

	//Context for the entire screen
	GrContext* sContext;
} Screen;

/**
 * Function to initialize the game screen.
 */
void initScreen(Screen* s);

/**
 * Function to destroy the screen.
 */
void destroyScreen(Screen* s);

/**
 * Function to draw the screen border.
 */
void drawScreenBorder(Screen* s);

/**
 * Function to render the shop status area.
 */
void renderStatusBar(Screen* s, Game* g);

/**
 * Function to render the title screen.
 */
void renderTitleScreen(Screen* s, int menuOption);

/**
 * Function to render screen text.
 */
void renderScreenText(char* t, int x, int y, GrColor fc, GrColor bc, GrFont* fnt);

/**
 * Function to render the screen.
 */
void render(Screen* s, Game* g);

#endif 
