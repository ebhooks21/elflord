/**
 * Player.c
 * Author: Eric Hooks, 2026
 * Purpose: To define player related functionality.
 */
#include "HEADER/PLAYER.H"
#include "HEADER/INV.H"
#include "HEADER/MAP.H"
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
	p->name = "Desryn\0";
	p->xLoc = 3.5;
	p->yLoc = 3.5;
	p->angle = 0;
	p->moveSpeed = .15f;
	p->rotSpeed = .1f;
	p->fov = M_PI / 3;
	p->currHP = 50;
	p->maxHP = 50;
	p->currMP = 20;
	p->maxMP = 20;
	p->gold = 35;

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
void movePlayer(Game* g, float mAmnt) {
	Player* p = g->p;

	//Calculate the player's movement
	float nextX = p->xLoc + (float)(cos(p->angle) * mAmnt);
	float nextY = p->yLoc + (float)(sin(p->angle) * mAmnt);

	if(isWalkable(g->currMap, nextX, p->yLoc)) {
		p->xLoc = nextX;
	}

	if(isWalkable(g->currMap, p->xLoc, nextY)) {
		p->yLoc = nextY;
	}
}

/**
 * Function to rotate the player.
 */
void rotatePlayer(Player* p, double amount) {
	p->angle += amount;

	if(p->angle < 0.0) {
		p->angle += M_PI * 2.0;
	}

	else if(p->angle >= M_PI * 2.0) {
		p->angle -= M_PI * 2.0;
	}
}