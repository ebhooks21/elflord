/**
 * Enemmy.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the enemey structure.
 */

#include "STATS.H"
#include "VEC2F.H"
#include "GAME.H"

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

	//Variable for the enemy's angle
	float angle;

	//Variable for the enemy's movement speed
	float moveSpeed;

	//Variable for the enemy's rotation speed
	float rotSpeed;

	//Variable for the enemy's field of view
	float fov;
} Enemy;

/**
 * Function to initialize the enemy.
 */
Enemy* initEnemy();

/**
 * Function to destroy the enemy.
 */
void destroyEnemy(Enemy* p);

/**
 * Function to move the enemy.
 */
void moveEnemy(Game* g, float mAmnt);

/**
 * Function to rotate the enemy.
 */
void rotateEnemy(Enemy* p, double amount);

/**
 * Function to calculate the enemy stats.
 */
void calculateEnemyStats(Enemy* p);

#endif