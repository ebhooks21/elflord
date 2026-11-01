/**
 * Texprov.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the texture provider.
 */

#include "HEADER/TEXPROV.H"
#include "HEADER/MAP.H"
#include "HEADER/GTEX.H"
#include <stdlib.h>

/**
 * Function to create a texture provider.
 */
TextureProvider* initTexProv(Map* m) {
	TextureProvider* tp = malloc(sizeof *tp);

	loadTextures(tp, m);	

	return tp;
}

/**
 * Function to destroy the texture provider.
 */
void destroyTextureProvider(TextureProvider* tp) {
	//Destroy the textures
	destroyGameTexture(tp->floorTexture);
	destroyGameTexture(tp->ceilingTexture);
	destroyGameTexture(tp->wallTexture);
	destroyGameTexture(tp->doorTexture);
}

/**
 * Function to load the textures.
 */
void loadTextures(TextureProvider* tp, Map* m) {
	//Load the textures
	//Load the floor texture 
	tp->floorTexture = createGameTexture(m->fTexPath, 0, 0);
	loadGameTexture(tp->floorTexture);

	//Load the ceiling texture 
	tp->ceilingTexture = createGameTexture(m->cTexPath, 0, 0);
	loadGameTexture(tp->ceilingTexture);

	//Load the wall texture
	tp->wallTexture = createGameTexture(m->wTexPath, 0, 0);
	loadGameTexture(tp->wallTexture);

	//Load the door texture
	tp->doorTexture = createGameTexture(m->dTexPath, 0, 0);
	loadGameTexture(tp->doorTexture);
}
