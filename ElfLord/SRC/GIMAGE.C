/**
 * Gimage.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement loading a game image.
 */
#include "HEADER/GIMAGE.H"
#include <GRX20.H>
#include <stdlib.h>

/**
 * Function to create a game image object.
 */
GameImage* createGameImage(char* p, int t, GrColor tc) {
	GameImage* i = malloc(sizeof *i);

	i->path = p;

	i->trans = t;

	if(i->trans) {
		i->tColor = tc;
	}

	else {
		i->tColor = 0;
	}

	return i;
}

/**
 * Function to destroy a game image.
 */
void destroyGameImage(GameImage* i) {
	//Destory the game image
	GrDestroyContext(i->image);
}

/**
 * Function to load a game image.
 */
int loadGameImage(GameImage* i) {
	//Query the image
	if(GrQueryPnm(i->path, &i->width, &i->height, &i->maxCVal) != -1) {
		//Load the image
		i->image = GrCreateContext(i->width, i->height, NULL, NULL);
		GrLoadContextFromPnm(i->image, i->path);
	}

	else {
		return -1;
	}
}

/**
 * Function to render the image in a given location, on a given context.
 */
void renderGameImage(GameImage* gi, GrContext* c, int x, int y) {
	GrColor color;

	//Loop over the image pixels and draw them on the framebuffer
	for(int i = 0; i < gi->height; i++) {
		for(int j = 0; j < gi->width; j++) {
			color = GrPixelC(gi->image, i, j);

			if(gi->trans) { 
				if(gi->tColor != color) {
					GrPlot((x + i), (y + j), color);
				}
			}

			else {
				GrPlot((x + i), (y + j), color);
			}
		}
	}
}
