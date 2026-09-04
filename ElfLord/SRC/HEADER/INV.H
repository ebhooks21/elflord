/**
 * Inv.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the inventory.
 */

#include "ITEM.H"
#include "ITEMTYP.H"

#ifndef INV_H
#define INV_H

#define MAX_INV_ITEMS 50

typedef struct {
	//An array of item pointers
	Item* items[MAX_INV_ITEMS];

	//Variable for the current number of items
	int numItems;
} Inventory;

/**
 * Function to initialize the inventory.
 */
Inventory* initInventory();

/**
 * Function to destory the inventory.
 */
void destroyInventory(Inventory* inv);

/**
 * Function to add an item to the inventory.
 */
void addItemToInventory(Inventory* inv, Item* i);

/**
 * Function to get an item in the inventory.
 */
Item* getItem(Inventory* inv, int index);

/**
 * Function to remove an item from the inventory.
 */
void removeItem(Inventory* inv, int index);

#endif