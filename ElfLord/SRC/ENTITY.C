/**
 * Entity.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the Entity functions.
 */
#include "HEADER/ENTITY.H"
#include "HEADER/ITEM.H"
#include "HEADER/ENEMY.H"
#include "HEADER/ENTTYP.H"
#include "HEADER/ESPRITET.H"
#include <stdlib.h>

/**
 * Function to initialize the entity.
 */
Entity* initEntity(EntityType t, float xPos, float yPos, float height, EntitySpriteType est) {
	Entity * e = malloc(sizeof *e);

	//Set the values
	e->ePos.x = xPos;
	e->ePos.y = yPos;
	e->type = t;
	e->height = height;
	
	//Preset the sprite id, as we won't have this yet
	e->spriteType = est;

	return e;
}

/**
 * Function to destroy the entity.
 */
void destroyEntity(Entity* e) {
	//Determine the type of entity to destroy
	switch(e->type) {
		case E_ENEMY:
			destroyEnemy(e->ent.enemy);
			break;

		case E_ITEM:
			//Items are only destoryed if they are still contained by the entity
			if(e->ent.item != NULL) {
				destroyItem(e->ent.item);
			}
			break;
	}

	free(e);
}
