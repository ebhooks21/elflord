/**
 * Item.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement item logic.
 */
#include "HEADER/ITEM.H"
#include "HEADER/ITEMTYP.H"
#include <stdlib.h>

/**
 * Function to initialize a item.
 */
Item* initItem() {
	return malloc(sizeof(Item));
}

/**
 * Function to destory an item.
 */
void destroyItem(Item* i) {
	free(i);
}