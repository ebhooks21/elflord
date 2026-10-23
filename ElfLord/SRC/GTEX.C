/**
 * Gtex.h
 * Author: Eric Hooks, 2026
 * Purpose: To implement the game texture, used for when pixel by pixel rendering is needed.
 */
#include "HEADER/GTEX.H"
#include <GRX20.H>
#include <stdlib.h>

/**
 * Function to create a game image object.
 */
GameTex* createGameTexture(char* p, int t, GrColor tc) {
	GameTex* tex = malloc(sizeof *tex);

	tex->path = p;

	tex->trans = t;

	if(tex->trans) {
		tex->tColor = tc;
	}

	else {
		tex->tColor = 0;
	}

	tex->tex = NULL;

	return tex;
}

/**
 * Function to destroy a game image.
 */
void destroyGameTexture(GameTex* t) {
	//Destory the game texture
	free(t->tex);
	free(t);
}

/**
 * Function to load a game image.
 */
int loadGameTexture(GameTex* t) {
	//Query the image
	if(GrQueryPnm(t->path, &t->width, &t->height, &t->maxCVal) != -1) {
		//Load the image
		GrContext* image = GrCreateContext(t->width, t->height, NULL, NULL);
		GrLoadContextFromPnm(image, t->path);

		t->tex = malloc(sizeof(GrColor) * t->width * t->height);

		for(int x = 0; x < t->width; x++) {
			for(int y = 0; y < t->height; y++) {
				t->tex[x * t->height + y] = GrPixelC(image, x, y);
			}
		}

		GrDestroyContext(image);
		return 0;
	}

	else {
		return -1;
	}
}