/**
 * Enemmy.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the enemey structure.
 */

#include "STATS.H"

//Forward delcare the Game structure
typedef struct game_t Game;

#ifndef ENEMY_H
#define ENEMY_H

//Define the enemy structure
typedef struct {
	//Variable for the enemy's name
	char* name;

	//Variable for the enemy's health
	int currHP;

	//Variabel for the enemy's max health
	int maxHP;

	//Variable for the enemy's current level
	int level;

	//Variable for the enemy's mp
	int currMP;

	//Variable for the enemy's max mp
	int maxMP;

	//Variable for the enemy's gold
	int gold;

	//Variable for the enemy's stats
	Stats stat;
} Enemy;

/**
 * Function to initialize the enemy.
 */
Enemy* initEnemy(char* name);

/**
 * Function to destroy the enemy.
 */
void destroyEnemy(Enemy* e);

/**
 * Function to move the enemy.
 */
void moveEnemy(Game* g, float mAmnt);

/**
 * Function to rotate the enemy.
 */
void rotateEnemy(Enemy* e, double amount);

/**
 * Function to calculate the enemy stats.
 */
void calculateEnemyStats(Enemy* e);

#endif
