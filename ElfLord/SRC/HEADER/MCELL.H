/**
 * Mcell.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the map cells.
 */

#include "MCELLTYP.H"

#ifndef MCELL_H
#define MCELL_H

typedef struct {
	//Variable for the integer representation
	char rep;

	//Variable for the map cell type
	MapCellType cType;

	//Variable for the map cell name
	char mapCellName[20];
}MapCell;

/**
 * Function to create a new map cell.
 */
MapCell* initMapCell(char cRep);

/**
 * Function to destroy a map cell.
 */
void destroyMapCell(MapCell* m);

/**
 * Function to convert a cell integer representation to a MapCellType.
 */
void convertIntRep(MapCell* m);

#endif
