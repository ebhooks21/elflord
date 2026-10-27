/**
 * Map.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the map and functions.
 */

 #include "MCELL.H"
 #include "MCELLTYP.H"

 #ifndef MAP_H
 #define MAP_H

 typedef struct {
	//Variable for the map rows
	int mapRows;

	//Variable for the map columns
	int mapCols;

	//Variable for the map data
	MapCell*** mapData;

    //Variable for the floor texture path
    char* fTexPath;

    //Variable for the ceiling texture path
    char* cTexPath;

    //Variable for the wall texture path
    char* wTexPath;
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
 MapCellType getMapCellType(Map* m, float x, float y);

 /**
  * Function to get the map cell object by id.
  */
 char* getMapCellObjById(int objId);

/**
 * Function to get a map cell.
 */
 MapCell* getMapCell(Map* m, float x, float y);

 #endif
