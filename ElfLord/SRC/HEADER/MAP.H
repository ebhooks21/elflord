/**
 * Map.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the map and functions.
 */

 #ifndef MAP_H
 #define MAP_H

 typedef struct {
	//Variable for the map rows
	int mapRows;

	//Variable for the map columns
	int mapCols;

	//Variable for the map data
	int** mapData;
 } Map;

 /**
  * Function to initialze the map.
  */
 Map* initMap(int rows, int cols);

 /**
  * Function to destroy the map.
  */
 void destroyMap(Map* m);

 /**
  * Function to see if an area is walkable.
  */
 int isWalkable(Map* m, float x, float y);

 #endif