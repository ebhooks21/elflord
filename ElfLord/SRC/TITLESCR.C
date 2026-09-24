/**
 * Titlescr.c
 * Author: Eric Hooks
 * Purpose: To handle rendering for the title screen.
 */
#include <GRX20.H>
#include <stdlib.h>
#include <stdio.h>
#include "HEADER/TITLESCR.H"
#include "HEADER/SCREEN.H"
#include "HEADER/MOUSE.H"
#include "HEADER/GSTATE.H"
#include "HEADER/GAME.H"

/**
 * Function to initialize the title screen.
 */
TitleScreen* initTitleScreen(Screen* s) {
	TitleScreen* t = malloc(sizeof *t);

	//Load the background image
    t->background = GrCreateContext(s->width, s->height, NULL, NULL);
    GrLoadContextFromPnm(t->background, "ASSET\\title.ppm");

	//Create the menu options
	createTitleScreenMenuOptions(t, s);

	//Set the text
	t->newGameText = "New Game";
	t->continueGameText = "Continue Game";
	t->returnToDosText = "Return to DOS";
	t->menuOption = 0;
}

/**
 * Function to destory the title screen.
 */
void destoryTitleScreen(TitleScreen* t) {
	//Destory the background
    GrDestroyContext(t->background);

	//Destory the screen
	free(t);
}

/**
 * Function to render the title screen.
 */
void renderTitleScreen(TitleScreen* t, Screen* s, Game* g) {
	//Variable for the screen text
	char tempText[25];

	//Write the background image
    GrBitBlt(s->frame, 0, 0, t->background, 0, 0, (s->width - 1), (s->height - 1), GrWRITE);

	for(int i = 0; i < 3; i++) {
		if(t->menuOption == i) {
			sprintf(tempText, "> %s <", t->mOpt[i]->text);
		}

		else {
			sprintf(tempText, "%s", t->mOpt[i]->text);
		}

		renderMenuOption(t->mOpt[i], tempText);
	}

    //Write the menu options to the screen
    // if(t->menuOption == 0) {
	// 	sprintf(tempText, "> %s <", t->mOpt[0]->text);
    // }

    // else {
	// 	sprintf(tempText, "%s", t->mOpt[0]->text);
    // }

	// renderScreenText(tempText, (int)(s->width / 2), (int)(s->height / 2), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);

    // if(t->menuOption == 1) {
	// 	sprintf(tempText, "> %s <", t->mOpt[1]->text);
    // }

    // else {
	// 	sprintf(tempText, "%s", t->mOpt[1]->text);
    // }

	// renderScreenText(tempText, (int)(s->width / 2), ((int)(s->height / 2) + 32), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);

    // if(t->menuOption == 2) {
	// 	sprintf(tempText, "> %s <", t->returnToDosText);
    // }

    // else {
	// 	sprintf(tempText, "%s", t->returnToDosText);
    // }

	// renderScreenText(tempText, (int)(s->width / 2), ((int)(s->height / 2) + 64), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
}

/**
 * Function to create the title screen options.
 */
void createTitleScreenMenuOptions(TitleScreen* t, Screen* s) {
	//Create a text option for the menu options
	GrTextOption* options = malloc(sizeof *options);

    options->txo_font = &GrFont_PC8x16;
    options->txo_fgcolor.v = GrWhite();
    options->txo_bgcolor.v = GrNOCOLOR;
    options->txo_chrtype = GR_BYTE_TEXT;
    options->txo_direct = GR_TEXT_RIGHT;
    options->txo_xalign = GR_ALIGN_CENTER;
    options->txo_yalign = GR_ALIGN_TOP;

	//Create the menu option for new game
	t->mOpt[0] = initMenuOption("New Game", (int)(s->width / 2), (int)(s->height / 2), options);

	//Create the menu option for continue game
	t->mOpt[1] = initMenuOption("Continue Game", (int)(s->width / 2), (int)(s->height / 2) + 32, options);

	//Create the menu option for return to dos
	t->mOpt[2] = initMenuOption("Return to DOS", (int)(s->width / 2), (int)(s->height / 2) + 64, options);
}

/**
 * Fucntion to handle title screen mouse movement.
 */
void handleTitleScreenMouseMovement(TitleScreen* t, Mouse* m, Game* g) {
	//Check to see if we are hovering over a particular input
	for(int i = 0; i < 3; i++) {
		MenuOption* mo = t->mOpt[i];

		if((m->mPos.x >= mo->left) && (m->mPos.x <= mo->right) && (m->mPos.y >= mo->top) && (m->mPos.y <= mo->bottom)) {
			t->menuOption = i;
		}
	}
}

/**
 * Fucntion to handle title screen mouse left button input.
 */
void handleTitleScreenMouseLeftButtonInput(TitleScreen* t, Mouse* m, Game* g) {
	handleTitleScreenAction(t, g);	
}

/**
 * Function to handle title screen action.
 */
void handleTitleScreenAction(TitleScreen* t, Game* g) {
	switch(t->menuOption) {
			case 0:
				g->state = GAME_START_NEW;
				break;
			
			case 2:
				g->state = EXIT_GAME;
				break;
		}
}