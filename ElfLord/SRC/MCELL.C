/**
 * Mcell.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the map cells.
 */

#include "HEADER/MCELL.H"
#include "HEADER/MCELLTYP.H"
#include <string.h>
#include <stdlib.h>

/**
 * Function to create a new map cell.
 */
MapCell* initMapCell(char cRep) {
	MapCell* m = malloc(sizeof *m);

	m->rep = cRep;
	convertIntRep(m);

	return m;
}

/**
 * Function to destroy a map cell.
 */
void destroyMapCell(MapCell* m) {
	free(m);
}

/**
 * Function to convert a cell integer representation to a MapCellType.
 */
void convertIntRep(MapCell* m) {
	switch(m->rep) {
		case '#':
			m->cType = M_CELL_WALL;
			strcpy(m->mapCellName, "Wall\0");
			break;

		case 'd':
			m->cType = M_CELL_DOOR;
			strcpy(m->mapCellName, "Door\0");
			break;

		case '.':
		default:
			m->cType = M_CELL_EMPTY;
			strcpy(m->mapCellName, "Empty\0");
			break;
	}
}

