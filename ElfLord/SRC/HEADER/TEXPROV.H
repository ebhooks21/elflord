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

typedef struct{
	//Variable for the ceiling texture
	GameTex* ceilingTexture;

	//Variable for the floor texture
	GameTex* floorTexture;

	//Variable for the wall texture
	GameTex* wallTexture;

	//Variable for the door texture
	GameTex* doorTexture;
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

#endif
