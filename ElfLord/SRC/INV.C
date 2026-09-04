/**
 * Inv.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the inventory.
 */
#include "HEADER/INV.H"
#include "HEADER/ITEM.H"
#include "HEADER/ITEMTYP.H"
#include <stdlib.h>

/**
 * Function to initialize the inventory.
 */
Inventory* initInventory() {
	//Create a new inventory
	Inventory* inv = malloc(sizeof *inv);

	//Set the initial number of items
	inv->numItems = 0;

	//Initialize the array
	for(int i = 0; i < MAX_INV_ITEMS; i++) {
		inv->items[i] = NULL;
	}

	return inv;
}

/**
 * Function to destory the inventory.
 */
void destroyInventory(Inventory* inv) {
	//Loop through and destory all items
	for(int i = 0; i < MAX_INV_ITEMS; i++) {
		destroyItem(inv->items[i]);
	}

	//Release the inventory
	free(inv);
}

/**
 * Function to add an item to the inventory.
 */
void addItemToInventory(Inventory* inv, Item* i) {
	//Insert the item at the current number of items(last index)
	inv->items[inv->numItems] = i;

	//Increment the number of items
	inv->numItems++;
}

/**
 * Function to get an item in the inventory.
 */
Item* getItem(Inventory* inv, int index){
	return inv->items[index];
}

/**
 * Function to remove an item from the inventory.
 */
void removeItem(Inventory* inv, int index) {
	//Remove the item at the index
	free(inv->items[index]);
	inv->items[index];

	//Shift all of the items down to fill in the holes
	for(int i = index; i < (MAX_INV_ITEMS - 1); i++) {
		if(inv->items[(i + 1)] != NULL) {
			inv->items[i] = inv->items[(i + 1)];
			inv->items[(i + 1)] = NULL;
		}
	}

	inv->numItems--;
}