/**
 * Maplo.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the functions needed for loading maps.
 */

 #include "MAP.H"

 #ifndef MAPLO_H
 #define MAPLO_H

/**
 * Function for loading a map.
 */
Map* loadMap(char* mapName);

/**
 * Function to parse the map width and height.
 */
void parseMapWidthHeight(char* fBuffer, int* width, int* height);

/**
 * Function to build the map row.
 */
void buildMapRow(Map* map, char* fBuffer, int currRow);

 #endif
