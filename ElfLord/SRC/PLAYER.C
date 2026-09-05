/**
 * Player.c
 * Author: Eric Hooks, 2026
 * Purpose: To define player related functionality.
 */
#include "HEADER/PLAYER.H"
#include "HEADER/INV.H"
#include <stdlib.h>
#include <math.h>

/**
 * Function to initialize the player.
 */
Player* initPlayer() {
	//Create a player
	Player* p = malloc(sizeof *p);

	//Initialize the player's inventory
	p->inv = initInventory();

	//Set initial player values
	p->xLoc = 3.5;
	p->yLoc = 3.5;
	p->angle = 0;
	p->moveSpeed = 3;
	p->rotSpeed = 2;
	p->fov = M_PI / 3;

	return p;
}

/**
 * Function to destroy the player.
 */
void destroyPlayer(Player* p) {
	//Destory the inventory
	destroyInventory(p->inv);

	free(p);
}

/**
 * Function to move the player.
 */
void movePlayer(Player* p, float mAmnt) {
	//Calculate the player's movement
	float nextX = p->xLoc + (float)(cos(p->angle) * mAmnt);
	float nextY = p->yLoc + (float)(sin(p->angle) * mAmnt);

	// if(isWalkable(nextX, p->yLoc)) {
	// 	p->xLoc = nextX;
	// }

	// if(isWalkable(p->xLoc, nextY)) {
	// 	p->yLoc = nextY;
	// }
}