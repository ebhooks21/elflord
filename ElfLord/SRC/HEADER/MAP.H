/**
 * Map.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the map and functions.
 */

 #include "MCELL.H"
 #include "MCELLTYP.H"
 #include "TEXPROV.H"
 #include "VEC2.H"

 #ifndef MAP_H
 #define MAP_H

 typedef struct map_t {
	//Variable for the map rows
	int mapRows;

	//Variable for the map columns
	int mapCols;

	//Variable for the map data
	MapCell*** mapData;

	//Variable for the player start position
	Vec2 pStart;

    //Variable for the floor texture path
    char* fTexPath;

    //Variable for the ceiling texture path
    char* cTexPath;

    //Variable for the wall texture path
    char* wTexPath;

	//Variable for the door texture path
	char* dTexPath;

	//Variable for the TextureProvider
	TextureProvider* texP;
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

/**
 * Function to load the map textures.
 */
void loadMapTextures(Map* m);

 #endif
