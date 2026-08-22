/**
 * Elflord.c
 * Author: Eric HOoks
 * Purpose: Main entry point for the Elflord game.
 */
#include "HEADER/GAME.H"
#include <stdlib.h>
#include <stdio.h>


 /**
  * Program entry point.
  */
 int main() {
	//Create a game reference
	Game* g = malloc(sizeof *g);

	//Start the game
	startGame(g);

	//Destroy the game
	destroyGame(g);

	//Release memory
	free(g);

	//Output thank you message
	freopen("CON", "w", stderr);
	fprintf(stderr, "Thank you for playing.\n");

	return 0;
 }
