/**
 * Helpscr.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the help screen.
 */

#include "HEADER/HELPSCR.H"
#include "HEADER/SCREEN.H"
#include "HEADER/GAME.H"
#include <GRX20.H>
#include <stddef.h>
#include <stdlib.h>

/**
 * Function to initialize the help screen.
 */
HelpScreen* initHelpScreen(Screen* s) {
	HelpScreen* ss = malloc(sizeof *ss);

	//Load the screen background
    ss->background = GrCreateContext(s->width, s->height, NULL, NULL);
    GrLoadContextFromPnm(ss->background, "ASSET\\paper.ppm");

	ss->page = 1;

	return ss;
}

/**
 * Function to dehelp the help screen.
 */
void destroyHelpScreen(HelpScreen* s) {
	//Destroy the background
    GrDestroyContext(s->background);
	free(s);
}

/**
 * Function to render the help screen.
 */
void renderHelpScreen(HelpScreen* ss, Screen* s, Game* g) {
	GrColor redColor = GrAllocColor(255, 0, 0);

    //Write the background image
    GrBitBlt(s->frame, 0, 0, ss->background, 0, 0, (s->width - 1), (s->height - 1), GrWRITE);

    //Write the text to the screen
	renderScreenText("HELP", (s->width / 2), 10, GR_ALIGN_CENTER, redColor, GrNOCOLOR, &GrFont_PC8x14);
	renderScreenText("Legend", (s->width /2), 30, GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("F1 -- Display Help", 7, 39, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("C -- Display Character Sheet", 7, 48, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("E -- Interact", 7, 56, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("Left Mouse Button -- Attack", 7, 64, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("W/Up Arrow -- Move Forward", 7, 72, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("S/Down Arrow -- Move Backward", 7, 80, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("A/Mouse -- Look Left", 7, 88, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("D/Mouse -- Look Right", 7, 96, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("ESC -- Exit to DOS", 7, 104, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);

	renderScreenText("How to Play", (s->width / 2), 116, GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("Collect all bags of gold and make it back to", (s->width / 2), 128, GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("the door.", (s->width / 2), 136, GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText("Dont Die!", (s->width / 2), 156, GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
}

/**
 * Function to handle help screen mouse left button input.
 */
void handleHelpScreenMouseLeftButtonInput(HelpScreen* s, Mouse* m, Game* g) {
	handleHelpScreenAction(s, g);	
}

/**
 * Function to handle help screen action.
 */
void handleHelpScreenAction(HelpScreen* s, Game* g) {
	if(s->page == 2) {	
		//This will accept any key, so just change state
		g->state = INIT;
	}

	else {
		s->page++;
	}
}