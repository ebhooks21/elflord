/**
 * Texprov.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the texture provider.
 */

#include "HEADER/TEXPROV.H"
#include "HEADER/MAP.H"
#include "HEADER/GTEX.H"
#include "HEADER/ESPRITET.H"
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

	//Destory all the sprites
	for(int i = 0; i < MAX_SPRITE_TEX; i++) {
		if(tp->entitySprites[i] != NULL) {
			destroyGameTexture(tp->entitySprites[i]);
		}
	}
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

/**
 * Function to load the sprite textures.
 */
void loadEntitySpriteTextures(TextureProvider* tp, Map* m) {
	GrColor tColor = GrAllocColor(255, 0, 255);

	//Load the entity sprites for the map
	//Current the map does not set the sprites, so we load all possible entity sprites
	for(int i = 0; i < MAX_SPRITE_TEX; i++) {
		tp->entitySprites[i] = NULL;
	}

	//Load the Gold sprite for now
	tp->entitySprites[I_GOLD] = createGameTexture("ASSET\\ITEM\\GOLD.PPM", 1, tColor);
	loadGameTexture(tp->entitySprites[I_GOLD]);
}
