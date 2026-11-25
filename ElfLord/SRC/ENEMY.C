/**
 * Enemy.c
 * Author: Eric Hooks, 2026
 * Purpose: To define enemy related functionality.
 */
#include "HEADER/ENEMY.H"
#include "HEADER/STATS.H"
#include "HEADER/MAPLO.H"
#include "HEADER/PLAYER.H"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * Function to initialize the enemy.
 */
Enemy* initEnemy(char* name) {
	//Create a enemy
	Enemy* e = malloc(sizeof *e);

	//Set initial enemy values
	e->name = dupStr(name);

	calculateEnemyStats(e);	

	return e;
}

/**
 * Function to destroy the enemy.
 */
void destroyEnemy(Enemy* e) {
	free(e->name);
	free(e);
}

/**
 * Function to move the enemy.
 */
void moveEnemy(Game* g, float mAmnt) {
	
}

/**
 * Function to rotate the enemy.
 */
void rotateEnemy(Enemy* e, double amount) {
	
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

	e->maxHP = 10 + (4 * (e->stat).con) + (5 * (e->level - 1));

	if(e->maxHP < 30) {
		e->maxHP = 30;
	}

	e->currHP = e->maxHP;

	e->maxMP = 10 + (2 * (e->stat).intel) + (3 * (e->level -1));

	if(e->maxMP < 20) {
		e->maxMP = 20;
	}

	e->currMP = e->maxMP;
}

/**
 * Function to melee attack the player.
 */
void meleeAttackPlayer(Enemy* e, Game* g, Player* p) {
	int hChance = (rand() % 10) + 1;
	int dmg = 0;
	char msg[30];

	if(hChance < 5) {
		//Miss
		sprintf(msg, "%s missed you.", e->name);
		addMessage(&g->msgA, msg);	
	}

	else {
		//Hit
		dmg = calculateEnemyMeleeHitDamage(e, p);
		p->currHP -= dmg;

		sprintf(msg, "You take %d damage.", dmg);
		addMessage(&g->msgA, msg);

		//Check to see if the player died
		if(p->currHP <= 0) {
			//Player died
			g->state = DEATH_SCREEN_INIT;
		}
	}
}

/**
 * Function to calculate enemy melee hit damage.
 */
int calculateEnemyMeleeHitDamage(Enemy* e, Player* p) {
	int dmg = 0;

	//Take into account enemy armor, resistences, etc.

	dmg += (rand() % 2) + 1;
	dmg *= e->stat.str;

	return dmg;
}
