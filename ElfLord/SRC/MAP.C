/**
 * Map.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement map related functions.
 */

 #include "HEADER/MAP.H"
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
	m->mapData = (int **)malloc((m->mapRows * sizeof(int *)));

	//Initialize the columns of the map
	for(int i = 0; i < m->mapRows; i++) {
		m->mapData[i] = (int *)malloc((m->mapCols * sizeof(int)));
	}

	//Pre-initialize all spots to 0
	for(int i = 0; i < m->mapRows; i++) {
		for(int j = 0; j < m->mapCols; j++) {
			m->mapData[i][j] = 0;
		}
	}

	return m;
 }

 /**
  * Function to destroy the map.
  */
 void destroyMap(Map* m) {
	//Destory each row and column
	for(int i = 0; i < m->mapRows; i++) {
		//Clear the rows
		free(m->mapData[i]);
	}

	//Free the map
	free(m);
 }

 /**
  * Function to see if a map position is walkable.
  */
 int isWalkable(Map* m, float x, float y) {
	int mapX = (int)floor(x);
	int mapY = (int)floor(y);

	if(mapX < 0 || mapX >= m->mapCols || mapY < 0 || mapY >= m->mapRows) {
		return 0;
	}

	return m->mapData[mapY][mapX] == 0;	
 }