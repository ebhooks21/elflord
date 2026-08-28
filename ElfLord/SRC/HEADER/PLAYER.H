/**
 * Player.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the player. 
 */

#ifndef PLAYER_H
#define PLAYER_H

//Define the player structure
typedef struct {
	//Variable for the player's health
	int currHP;

	//Variabel for the player's max health
	int maxHP;

	//Variable for the player's current level
	int level;

	//Variable for the player's mp
	int currMP;

	//Variable for the player's max mp
	int maxMP;

	//Variable for the player's gold
	int gold;

	//Variable for the player's x location
	float xLoc;

	//Variable for the player's y location
	float yLoc;

	//Variable for the player's angle
	float angle;

	//Variable for the player's movement speed
	int moveSpeed;

	//Variable for the player's rotation speed
	int rotSpeed;

	//Variable for the player's field of view
	float fov;
} Player;

/**
 * Function to move the player.
 */
void movePlayer(Player* p, float mAmnt);

#endif