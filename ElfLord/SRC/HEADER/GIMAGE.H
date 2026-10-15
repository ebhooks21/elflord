/**
 * Gimage.h
 * Author: Eric Hooks
 * Purpose: To define the game image functionality.
 */
#include <GRX20.H>

#ifndef GIMAGE_H
#define GIMAGE_H

typedef struct {
	//Variable for the image path
	char* path;

	//Variable for the game image
	GrContext* image;

	//Variables for the width and height
	int width;
	int height;

	//Variable the max color value
	int maxCVal;

	//Variable for the if the image supports transparency
	int trans;

	//Variable for the transparency color
	GrColor tColor;
} GameImage;

/**
 * Function to create a game image object.
 */
GameImage* createGameImage(char* p, int t, GrColor tc);

/**
 * Function to destroy a game image.
 */
void destroyGameImage(GameImage* i);

/**
 * Function to load a game image.
 */
int loadGameImage(GameImage* i);

#endif