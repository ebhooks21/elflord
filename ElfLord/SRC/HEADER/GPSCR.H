/**
 * Gpscr.h
 * Author: Eric Hooks
 * Purpose: To define the game play screen, where actions happen.
 */
#include "SCREEN.H"
#include "GAME.H"

#ifndef GPSCR_H
#define GPSCR_H

typedef struct {
	//Variable for the game area width
	int gAreaWidth;

	//Variable for the game area height
	int gAreaHeight;

	//Variable for the hud area width
	int hAreaWidth;

	//Variable for the hud area height
	int hAreaHeight;
} GamePlayScreen;

/**
 * Function to render the game play screen.
 */
void renderGameplayScreen(Screen* s, Game* g);

/**
 * Function to render the game play area.
 */
void renderGameplayArea(Screen* s, Game* g);

/**
 * Function to render the hud area.
 */
void renderHudArea(Screen* s, Game* g);

#endif