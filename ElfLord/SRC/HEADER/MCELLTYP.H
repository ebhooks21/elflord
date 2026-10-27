/**
 * Mcelltyp.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the map cell types.
 */

#ifndef MCELLTYP_H
#define MCELLTYP_H

typedef enum {
	M_CELL_EMPTY,
	M_CELL_WALL,
	M_CELL_DOOR,
	M_CELL_GATE,
	M_CELL_HIDDEN
}MapCellType;

#endif
