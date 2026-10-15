/**
 * Stats.h
 * Author: Eric Hooks, 2026
 * Purpose: To define a struct to hold entity stats.
 */

#ifndef STATS_H
#define STATS_H

typedef struct {
	//Variable for Strength
	int str;

	//Varaible for dexterity
	int dex;

	//Variable for constitution
	int con;

	//Variable for intelligence
	int intel;

	//Variable for luck
	int luck;

	//Variable for currExp
	int currExp;

	//Variable for nextExp
	int nextExp;

	//Variable for totalExp
	int totalExp;
} Stats;

#endif