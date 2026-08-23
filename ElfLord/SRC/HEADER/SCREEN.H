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

	//Context for a given frame
	GrContext* frame;

	//Variable for the color red
	GrColor red;
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
void drawScreenBorder(Screen* s, GrColor c);

/**
 * Function to render the shop status area.
 */
void renderStatusBar(Screen* s, Game* g);

/**
 * Function to render the title screen.
 */
void renderTitleScreen(Screen* s, int menuOption);

/**
 * Function to render the story screen.
 */
void renderStoryScreen(Screen* s, Game* g);

/**
 * Function to render screen text.
 */
void renderScreenText(char* t, int x, int y, int align, GrColor fc, GrColor bc, GrFont* fnt);

/**
 * Function to render the screen.
 */
void render(Screen* s, Game* g);

/**
 * Function to unload the background.
 */
void unloadBackground(Screen* s);

/**
 * Function to load a background.
 */
void loadBackground(Screen* s, char* backgroundPath);
	
#endif 
