/**
 * Player.c
 * Author: Eric Hooks, 2026
 * Purpose: To define player related functionality.
 */
#include "HEADER/PLAYER.H"
#include <math.h>

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