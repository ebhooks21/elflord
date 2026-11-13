/**
 * Texprov.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the texture provider.
 */

#include "GTEX.H"
#include <GRX20.H>

typedef struct map_t Map;

#ifndef TEXPROV_H
#define TEXPROV_H

#define MAX_SPRITE_TEX 30

typedef struct{
	//Variable for the ceiling texture
	GameTex* ceilingTexture;

	//Variable for the floor texture
	GameTex* floorTexture;

	//Variable for the wall texture
	GameTex* wallTexture;

	//Variable for the door texture
	GameTex* doorTexture;

	//Variable for entity sprites
	GameTex* entitySprites[MAX_SPRITE_TEX];
}TextureProvider;

/**
 * Function to create a texture provider.
 */
TextureProvider* initTexProv(Map* m);

/**
 * Function to destroy the texture provider.
 */
void destroyTextureProvider(TextureProvider* tp);

/**
 * Function to load the textures.
 */
void loadTextures(TextureProvider* tp, Map* m);

/**
 * Function to load the sprite textures.
 */
void loadEntitySpriteTextures(TextureProvider* tp, Map* m);

#endif
