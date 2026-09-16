/**
 * Gpscr.h
 * Author: Eric Hooks
 * Purpose: To define the game play screen, where actions happen.
 */
#include "SCREEN.H"
#include "GAME.H"
#include "MAP.H"
#include <GRX20.H>

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

	//Variable for the hud background
	GrContext* hudBackground;

	//Variable for the floor texture
	GrContext* floorTexture;

	//Variable for the ceiling texture
	GrContext* ceilingTexture;

	//Variable for teh scrolling floor scanline
	GrColor* floorScanline;
} GamePlayScreen;

/**
 * Function to initialize the gameplay screen.
 */
GamePlayScreen* initGPScr(Screen* s);

/**
 * Function to destroy the gameplay screen.
 */
void destoryGPScr(GamePlayScreen* g);

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