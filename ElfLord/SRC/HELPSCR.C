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
	if(ss->page == 1) {
		renderScreenText("CONGRATULATIONS!", (s->width / 2), 10, GR_ALIGN_CENTER, redColor, GrNOCOLOR, &GrFont_PC8x14);
		renderScreenText("You found the gold and cleared the dungeon!", (s->width /2), 30, GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("This game was a demo, and is therefore incomplete.", 7, 50, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("I hope you enjoyed playing it as much as", (s->width / 2), 70, GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("I enjoyed making it.", (s->width / 2), 90, GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("If you did, please let me know. I hope to finish it", 7, 110, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("and have a full release of the game at some point.", 7, 130, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("Thanks for Playing!", (s->width / 2), 150, GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	}
	
	if(((s->rCount / 120) % 2) == 0) {
			renderScreenText("PRESS ANY KEY TO CONTINUE...", ((int)(s->width / 2) + 6), 180, GR_ALIGN_CENTER, s->red, GrNOCOLOR, &GrFont_PC8x14);
	}
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