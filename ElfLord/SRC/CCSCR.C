/**
 * Ccscr.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the close confirmation screen.
 */
#include "HEADER/CCSCR.H"
#include "HEADER/SCREEN.H"
#include "HEADER/GAME.H"
#include "HEADER/GIMAGE.H"
#include <GRX20.H>
#include <stdlib.h>

/**
 * Function to initialize the close confirmation screen.
 */
CloseConfirmScreen* initCloseConfirmScreen(Screen* s) {
	CloseConfirmScreen* c = malloc(sizeof *c);

	//Load the screen background
	c->background = createGameImage("ASSET\\paper.ppm", 0, 0);
	loadGameImage(c->background);

	return c;
}

/**
 * Function to destroy the close confirmation screen.
 */
void destroyCloseConfirmationScreen(CloseConfirmScreen* c) {
	//Destroy the background
	destroyGameImage(c->background);

	//Free the screen
	free(c);
}

/**
 * Function to render the close confirmation screen.
 */
void renderCloseConfirmationScreen(CloseConfirmScreen* c, Screen* s, Game* g) {
	//Write the background image
    GrBitBlt(s->frame, 0, 0, (c->background)->image, 0, 0, ((c->background)->width - 1), ((c->background)->height - 1), GrWRITE);	

	
	renderScreenText("RETURN TO DOS? (Y/N)", ((c->background)->width / 2), ((c->background)->height / 2), GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC8x14);
}