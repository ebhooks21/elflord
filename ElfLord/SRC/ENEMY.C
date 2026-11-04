/**
 * Enemy.c
 * Author: Eric Hooks, 2026
 * Purpose: To define enemy related functionality.
 */
#include "HEADER/ENEMY.H"
#include "HEADER/STATS.H"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/**
 * Function to initialize the enemy.
 */
Enemy* initEnemy(char* name) {
	//Create a enemy
	Enemy* e = malloc(sizeof *e);

	//Set initial enemy values
	strcpy(e->name, name);

	srand(time(NULL));

	calculateEnemyStats(e);	

	return e;
}

/**
 * Function to destroy the enemy.
 */
void destroyEnemy(Enemy* e) {
	free(e);
}

/**
 * Function to move the enemy.
 */
void moveEnemy(Game* g, float mAmnt) {
	/*Enemy* p = g->p;

	//Variable for the area the enemy is walking to
	MapCell* mcX;
	MapCell* mcY;
	char status[30];

	//Calculate the enemy's movement
	float nextX = p->xLoc + (float)(cos(p->angle) * mAmnt);
	float nextY = p->yLoc + (float)(sin(p->angle) * mAmnt);

	mcX = getMapCell(g->currMap, nextX, p->yLoc);
	if(mcX->cType == M_CELL_EMPTY) {
		p->xLoc = nextX;
	}

	mcY = getMapCell(g->currMap, p->xLoc, nextY);
	if(mcY->cType == M_CELL_EMPTY) {
		p->yLoc = nextY;
	}

	//We didn't move
	if(mcX->cType != M_CELL_EMPTY) {
		sprintf(status, "You hit a %s.", mcX->mapCellName);
		addMessage(&g->msgA, status);
	}

	else if(mcY->cType != M_CELL_EMPTY) {
		sprintf(status, "You hit a %s.", mcY->mapCellName);
		addMessage(&g->msgA, status);
	}*/
}

/**
 * Function to rotate the enemy.
 */
void rotateEnemy(Enemy* e, double amount) {
	/*p->angle += amount;

	if(p->angle < 0.0) {
		p->angle += M_PI * 2.0;
	}

	else if(p->angle >= M_PI * 2.0) {
		p->angle -= M_PI * 2.0;
	}*/
}

/**
 * Function to calculate the enemy stats.
 */
void calculateEnemyStats(Enemy* e) {
	e->level = 1;

	e->gold = (rand() % (10 * e->level)) + 1;
	(e->stat).currExp = 0;
	(e->stat).str = (rand() % 10) + 1;
	(e->stat).con = (rand() % 10) + 1;
	(e->stat).dex = (rand() % 10) + 1;
	(e->stat).luck = (rand() % 10) + 1;
	(e->stat).intel = (rand() % 10) + 1;
	(e->stat).nextExp = (int)floor(50 + (e->level * 0.10f));
	(e->stat).totalExp = 0;

	e->maxHP = 30 + (4 * (e->stat).con) + (5 * (e->level - 1));

	if(e->maxHP < 50) {
		e->maxHP = 50;
	}

	e->currHP = e->maxHP;

	e->maxMP = 10 + (2 * (e->stat).intel) + (3 * (e->level -1));

	if(e->maxMP < 20) {
		e->maxMP = 20;
	}

	e->currMP = e->maxMP;
}
