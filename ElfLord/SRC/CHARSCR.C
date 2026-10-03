/**
 * Charscr.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the character screen.
 */
#include "HEADER/CHARSCR.H"
#include "HEADER/GAME.H"
#include "HEADER/SCREEN.H"
#include <GRX20.H>
#include <stdlib.h>

/**
 * Function to initialize the character screen.
 */
CharacterScreen* initCharacterScreen(Screen* s) {
	CharacterScreen* c = malloc(sizeof *c);

	//Load the screen background
	c->background = GrCreateContext(s->width, s->height, NULL, NULL);
	GrLoadContextFromPnm(c->background, "ASSET\\paper.ppm");

	c->page = 1;

	return c;
}

/**
 * Function to destroy the character screen.
 */
void destroyCharacterScreen(CharacterScreen* c) {
	//Destroy the background
	GrDestroyContext(c->background);
	free(c);
}

/**
 * Function to render the character screen.
 */
void renderCharacterScreen(CharacterScreen* c, Screen* s, Game* g) {
	//Write the background image
    GrBitBlt(s->frame, 0, 0, c->background, 0, 0, (s->width - 1), (s->height - 1), GrWRITE);
}

/**
 * Function to handle character screen mouse movement.
 */
void handleCharacterScreenMouseMovement(CharacterScreen* c, Mouse* m, Game* g) {

}

/**
 * Function to handle character screen mouse left button input.
 */
void handleCharacterScreenMouseLeftButtonInput(CharacterScreen* c, Mouse* m, Game* g) {
	handleCharacterScreenAction(c, g);	
}

/**
 * Function to handle character screen action.
 */
void handleCharacterScreenAction(CharacterScreen* c, Game* g) {
	
}