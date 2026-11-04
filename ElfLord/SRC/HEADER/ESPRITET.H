/**
 * Espritet.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the Entity Sprite Types.
 * This is done because an entity can be either an item or a enemy.
 * Enemies and items can have different sprites, but we store this type
 * on the entity so that we don't tie a sprite to an object that isn't rendered.
 */

#ifndef ESPRITET_H
#define ESPRITET_H

typedef enum {
	E_SKELETON,
	I_GOLD
} EntitySpriteType;

/**
 * Function to look up an entity sprite from a type.
 */
char* convertEntityTypeToSprite(EntitySpriteType t);

#endif

