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
} Item;


#endif
