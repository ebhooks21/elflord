/**
 * Map.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement map related functions.
 */

 #include "HEADER/MAP.H"
 #include "HEADER/MCELL.H"
 #include "HEADER/MCELLTYP.H"
 #include "HEADER/GAME.H"
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

	m->cTexPath = NULL;
	m->fTexPath = NULL;
	m->wTexPath = NULL;

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
