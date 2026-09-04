/**
 * Item.h
 * Author: Eric Hooks, 2026
 * Purpose: To define a game item.
 */
#include "ITEMTYP.H"

#ifndef ITEM_H
#define ITEM_H

typedef struct {
    //Variable for the item name
    char* name;

    //Variable for the item type
    ItemType type;

    //Variable for the amount of health an item gives(or subtracts)
    int hpMod;

    //Variable for the price of the item
    int price;
} Item;

/**
 * Function to initialize an item.
 */
Item* initItem();

/**
 * Function to destory an item.
 */
void destroyItem(Item* i);

#endif
