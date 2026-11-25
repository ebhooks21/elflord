/**
 * Dscreen.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the death screen.
 */

#include "HEADER/DSCREEN.H"
#include "HEADER/SCREEN.H"
#include "HEADER/GAME.H"
#include <GRX20.H>
#include <stddef.h>
#include <stdlib.h>

/**
 * Function to initialize the death screen.
 */
DeathScreen* initDeathScreen(Screen* s) {
	DeathScreen* ds = malloc(sizeof *ds);

	//Load the screen background
    ds->background = GrCreateContext(s->width, s->height, NULL, NULL);
    GrLoadContextFromPnm(ds->background, "ASSET\\paper.ppm");

	return ds;
}

/**
 * Function to dehelp the death screen.
 */
void destroyDeathScreen(DeathScreen* s) {
	//Destroy the background
    GrDestroyContext(s->background);
	free(s);
}

/**
 * Function to render the death screen.
 */
void renderDeathScreen(DeathScreen* ds, Screen* s, Game* g) {
	GrColor redColor = GrAllocColor(255, 0, 0);

    //Write the background image
    GrBitBlt(s->frame, 0, 0, ds->background, 0, 0, (s->width - 1), (s->height - 1), GrWRITE);

    //Write the text to the screen
	renderScreenText("YOU DIED!", (s->width / 2), (s->height / 2), GR_ALIGN_CENTER, redColor, GrNOCOLOR, &GrFont_PC8x16);
	renderScreenText("Press Any Key To Exit", (s->width / 2), ((s->height / 2) + 40), GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
}

/**
 * Function to handle death screen mouse left button input.
 */
void handleDeathScreenMouseLeftButtonInput(DeathScreen* s, Mouse* m, Game* g) {
	handleDeathScreenAction(s, g);	
}

/**
 * Function to handle death screen action.
 */
void handleDeathScreenAction(DeathScreen* s, Game* g) {
}