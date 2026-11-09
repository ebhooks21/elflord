/**
 * Entity.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the Entity struct.
 */

#include "ITEM.H"
#include "ENEMY.H"
#include "ENTTYP.H"
#include "ESPRITET.H"
#include "VEC2F.H"

#ifndef ENTITY_H
#define ENTITY_H

typedef struct {
	//Variable for the entity's location
	Vec2f ePos;

	//Variable for the entity's height
	float height;

	//Variable for the sprite id in the entities sprite array
	EntitySpriteType spriteType;

	//Variable for if the entity is active on the map
	int active;

	//Variable for the type of entity
	EntityType type;

	//Variable for the entity data
	union {
		//Variable for an enemy
		Enemy* enemy;

		//Variable for an item
		Item* item;
	} ent;
} Entity;

/**
 * Function to initialize the entity.
 */
Entity* initEntity(EntityType t, float xPos, float yPos, float height, EntitySpriteType est);

/**
 * Function to destroy the entity.
 */
void destroyEntity(Entity* e);

#endif
