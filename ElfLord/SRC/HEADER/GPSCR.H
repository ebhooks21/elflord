/**
 * Gpscr.h
 * Author: Eric Hooks
 * Purpose: To define the game play screen, where actions happen.
 */
#include "SCREEN.H"
#include "GAME.H"
#include "VEC2F.H"
#include "VEC2.H"
#include "GIMAGE.H"
#include "GTEX.H"
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

	//Variable for the render direction
	Vec2f rDir;

	//Variable for the player viewing plane
	Vec2f pViewPlane;

	//Variable for the change in distance
	Vec2f deltaDist;

	//Variable for cell render locations
	Vec2 cellPos;

	//Variable for texture positions
	Vec2 texPos;

	//Variable for the hoizon line
	int horLine;

	//Variable for the camera height
	float cHeight;

	//Variable for the hud background
	GameImage* hudBackground;

	//Variable for the floor texture
	GameTex* floorTexture;

	//Variable for the ceiling texture
	GameTex* ceilingTexture;

	//Variable for the wall texture
	GameTex* wallTexture;

	//Variable for the frame buffer
	GrColor* frameBuffer;
} GamePlayScreen;

/**
 * Function to initialize the gameplay screen.
 */
GamePlayScreen* initGPScr(Screen* s, Map* map);

/**
 * Function to destroy the gameplay screen.
 */
void destoryGPScr(GamePlayScreen* g);

/**
 * Function to render the game play screen.
 */
void renderGameplayScreen(Screen* s, Game* g);

/**
 * Function to render the floor.
 */
void renderFloor(Screen* s, Game* g, GamePlayScreen* gps);

/**
 * Function to render the ceiling.
 */
void renderCeiling(Screen* s, Game* g, GamePlayScreen* gps);

/**
 * Function to render the walls.
 */
void renderWalls(Screen* s, Game* g, GamePlayScreen* gps);

/**
 * Function to render the game play area.
 */
void renderGameplayArea(Screen* s, Game* g);

/**
 * Function to render the hud area.
 */
void renderHudArea(Screen* s, Game* g);

#endif
