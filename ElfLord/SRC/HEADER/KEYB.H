/**
 * File Name: KEYB.H
 * Author: Eric Hooks, 2026
 * Purpose: To hold the functions for key handling.
 */

#ifndef KEYB_H
#define KEYB_H

#include<GRXKEYS.H>

//Forward declare the game structure
typedef struct game_t Game;

/**
 * Function to handle title screen input.
 */
void handleTitleScreenKeyInput(Game* g, GrKeyType key);

/**
 * Function to handle generic input.
 */
void handleGenericKeyInput(Game* g, GrKeyType key);

/**
 * Function to handle keypresses.
 */
void processKeyInput(Game* g);

#endif 