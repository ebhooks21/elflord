/**
 * Map.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement map related functions.
 */

 #include "HEADER/MAP.H"
 #include "HEADER/MCELL.H"
 #include "HEADER/MCELLTYP.H"
 #include "HEADER/GAME.H"
 #include "HEADER/ENTITY.H"
 #include <stdlib.h>
 #include <math.h>

/**
  * Function to initialze the map.
  */
 Map* initMap(int rows, int cols) {
	Map* m = malloc(sizeof *m);

	m->mapRows = rows;
	m->mapCols = cols;

	//Initialize the rows of the map
	m->mapData = (MapCell ***)malloc((m->mapRows * sizeof(MapCell **)));

	//Initialize the columns of the map
	for(int i = 0; i < m->mapRows; i++) {
		m->mapData[i] = (MapCell **)malloc((m->mapCols * sizeof(MapCell *)));
	}

	//Pre-initialize all spots to 0
	for(int i = 0; i < m->mapRows; i++) {
		for(int j = 0; j < m->mapCols; j++) {
			m->mapData[i][j] = NULL;
		}
	}

	m->texP = NULL;

	m->cTexPath = NULL;
	m->fTexPath = NULL;
	m->wTexPath = NULL;
	m->dTexPath = NULL;

	//Setup the entity storage
	for(int i = 0; i < MAX_MAP_ENT; i++) {
		m->entities[i] = NULL;
	}

	m->numEntites = 0;
	m->numGold = 0;

	return m;
 }

 /**
  * Function to destroy the map.
  */
 void destroyMap(Map* m) {
	//Destory each row and column
	for(int i = 0; i < m->mapRows; i++) {
		for(int y = 0; y < m->mapCols; y++) {
			//Clear the cols
			destroyMapCell(m->mapData[i][y]);
		}

		//Clear the rows
		free(m->mapData[i]);
	}

	//Destroy all entities
	for(int i = 0; i < MAX_MAP_ENT; i++) {
		if(m->entities[i] != NULL) {
			destroyEntity(m->entities[i]);
		}
	}

	//Free the map
	free(m);
 }

 /**
  * Function to see if a map position is walkable.
  * If it is walkable, it returns 0
  * If it is unwalkable, it returns the id of the object in front of the player
  */
 MapCellType getMapCellType(Map* m, float x, float y) {
	int mapX = (int)floor(x);
	int mapY = (int)floor(y);

	if(mapX < 0 || mapX >= m->mapCols || mapY < 0 || mapY >= m->mapRows) {
		return M_CELL_WALL;
	}

	return (m->mapData[mapY][mapX])->cType;
 }

 /**
  * Function to get the map cell object by id.
  */
 char* getMapCellObjById(int objId) {
	 return "Wall";
 }

/**
 * Function to get a map cell.
 */
 MapCell* getMapCell(Map* m, float x, float y) {
	int mapX = (int)floor(x);
	int mapY = (int)floor(y);

	if(mapX < 0 || mapX >= m->mapCols || mapY < 0 || mapY >= m->mapRows) {
		return NULL;
	}

	return m->mapData[mapY][mapX];
 }

/**
 * Function to load the map textures.
 */
void loadMapTextures(Map* m) {
	m->texP = initTexProv(m);
}

/**
 * Function to add an entity to the map.
 */
void addEntityToMap(Map* m, Entity* e) {
	if(m->numEntites < MAX_MAP_ENT) {
		m->entities[m->numEntites] = e;
		m->numEntites++;
	}
}

/**
 * Function to check entity/player proximity.
 */
Entity* checkPlayerProximity(Map* m, Player* p) {
	Vec2f distance;
	Entity* currEntity = NULL;
	int radius = 1;

	//Loop through the entities and check proximity to the player
	for(int i = 0; i < m->numEntites; i++) {
		if(m->entities[i]->active) {
			currEntity = m->entities[i];

			//Only check active entities
			distance.x = fabsf((currEntity->ePos).x - p->pPos.x);
			distance.y = fabsf((currEntity->ePos).y - p->pPos.y); 

			if((distance.x * distance.x + distance.y * distance.y) <= (radius * radius)) {
				return currEntity;
			}
		}
	}

	return NULL;
}

/**
 * Function to check what the player is looking at.
 */
MapCell* checkPlayerLookingAt(Map* m, Player* p) {
	//Variable for the area the player is walking to
	MapCell* mc;
	float reach = 1.0;

	//Calculate the player's movement
	float nextX = p->pPos.x + (float)(cos(p->angle) * reach);
	float nextY = p->pPos.y + (float)(sin(p->angle) * reach);

	mc = getMapCell(m, nextX, p->pPos.y);
	if(mc->cType != M_CELL_EMPTY) {
		return mc;
	}

	mc = getMapCell(m, p->pPos.x, nextY);
	if(mc->cType != M_CELL_EMPTY) {
		return mc;
	}

	return NULL;
}

/**
 * Function to perform entity actions.
 */
void performEntityActions(Map* m, Game* g, Player* p) {
	Entity* currEntity = NULL;
	int canAct = 0;

	//Loop through the entities and check if any can perform actions
	for(int i = 0; i < m->numEntites; i++) {
		if(m->entities[i]->active) {
			currEntity = m->entities[i];

			switch(currEntity->type) {
				case E_ENEMY:
					//Check to see if the player is near the enemy
					canAct = checkEnemyPlayerProximity(currEntity, p);

					if(canAct) {
						meleeAttackPlayer(currEntity->ent.enemy, g, p);
					}
					break;

				default:
					break;
			}
		}
	}
}
