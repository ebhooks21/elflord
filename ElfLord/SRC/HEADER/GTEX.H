/**
 * Gtex.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the game texture, used for when pixel by pixel rendering is needed.
 */
#include <GRX20.H>

#ifndef GTEX_H
#define GTEX_H

typedef struct {
	//Variable for the image path
	char* path;

	//Variable for the game texture cache
	GrColor* tex;

	//Variables for the width and height
	int width;
	int height;

	//Variable the max color value
	int maxCVal;

	//Variable for the if the image supports transparency
	int trans;

	//Variable for the transparency color
	GrColor tColor;
} GameTex;

/**
 * Function to create a game texture object.
 */
GameTex* createGameTexture(char* p, int t, GrColor tc);

/**
 * Function to destroy a game texture.
 */
void destroyGameTexture(GameTex* t);

/**
 * Function to load a game texture.
 */
int loadGameTexture(GameTex* t);

#endif