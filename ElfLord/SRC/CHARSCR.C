/**
 * Charscr.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the character screen.
 */
#include "HEADER/CHARSCR.H"
#include "HEADER/GAME.H"
#include "HEADER/SCREEN.H"
#include "HEADER/MENUOPT.H"
#include <GRX20.H>
#include <stdlib.h>
#include <stdio.h>

/**
 * Function to initialize the character screen.
 */
CharacterScreen* initCharacterScreen(Screen* s) {
	CharacterScreen* c = malloc(sizeof *c);

	//Load the screen background
	c->background = GrCreateContext(s->width, s->height, NULL, NULL);
	GrLoadContextFromPnm(c->background, "ASSET\\paper.ppm");

	//Create the character screen menu options
	createCharacterScreenMenuOptions(c, s);

	//Create the close menu option
	createCharacterScreenCloseOption(c, s);

	c->state = CHARACTER_SHEET;

	return c;
}

/**
 * Function to destroy the character screen.
 */
void destroyCharacterScreen(CharacterScreen* c) {
	//Destroy the background
	GrDestroyContext(c->background);

	//Destroy the menu options
	for(int i = 0; i < 4; i++) {
		destroyMenuOption(c->mOpt[i]);
	}

	//Destroy the screen
	free(c);
}

/**
 * Function to render the character screen.
 */
void renderCharacterScreen(CharacterScreen* c, Screen* s, Game* g) {
	//Variable for the screen text
	char tempText[25];

	//Write the background image
    GrBitBlt(s->frame, 0, 0, c->background, 0, 0, (s->width - 1), (s->height - 1), GrWRITE);

	//Render elements that are always on the screen, no matter the state
	//Render the menu options
	for(int i = 0; i < 4; i++) {
		if(c->state == i) {
			sprintf(tempText, "> %s <", c->mOpt[i]->text);
		}

		else {
			sprintf(tempText, "%s", c->mOpt[i]->text);
		}

		renderMenuOption(c->mOpt[i], tempText);
	}

	//Render the close button
	renderMenuOption(c->closeOpt, NULL);

	//Render the subscreen based upon the state
	switch(c->state) {
		case CHARACTER_SHEET:
			renderScreenText("Character Sheet", (int)(s->width / 2), 20, GR_ALIGN_CENTER, GrBlack(), GrNOCOLOR, &GrFont_PC8x16);
			break;
	}
}

/**
 * Function to create the character screen options.
 */
void createCharacterScreenMenuOptions(CharacterScreen* c, Screen* s) {
	//Create a text option for the menu options
	GrTextOption* options = malloc(sizeof *options);

    options->txo_font = &GrFont_PC6x8;
    options->txo_fgcolor.v = GrBlack();
    options->txo_bgcolor.v = GrNOCOLOR;
    options->txo_chrtype = GR_BYTE_TEXT;
    options->txo_direct = GR_TEXT_RIGHT;
    options->txo_xalign = GR_ALIGN_CENTER;
    options->txo_yalign = GR_ALIGN_TOP;

	//Create the menu option for new game
	c->mOpt[0] = initMenuOption("Character", 45, 8, options);

	//Create the menu option for continue game
	c->mOpt[1] = initMenuOption("Inventory", ((c->mOpt[0])->pos.x + ((c->mOpt[0]->width)) + 15), 8, options);

	//Create the menu option for return to dos
	c->mOpt[2] = initMenuOption("Equipment", ((c->mOpt[1])->pos.x + ((c->mOpt[1]->width)) + 15), 8, options);
	
	//Create the menu option for return to dos
	c->mOpt[3] = initMenuOption("Spells", ((c->mOpt[2])->pos.x + ((c->mOpt[2]->width)) + 15), 8, options);
}

/**
 * Function to create the character screen close button.
 */
void createCharacterScreenCloseOption(CharacterScreen* c, Screen* s) {
	//Create a text option for the menu options
	GrTextOption* options = malloc(sizeof *options);

    options->txo_font = &GrFont_PC8x16;
    options->txo_fgcolor.v = GrBlack();
    options->txo_bgcolor.v = GrNOCOLOR;
    options->txo_chrtype = GR_BYTE_TEXT;
    options->txo_direct = GR_TEXT_RIGHT;
    options->txo_xalign = GR_ALIGN_CENTER;
    options->txo_yalign = GR_ALIGN_TOP;

	//Create the menu option for new game
	c->closeOpt = initMenuOption("X", (s->width - 10), 5, options);
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
	if(checkClosedClicked(c, m)) {
		//Restore the gameplay screen
		g->state = GAMEPLAY_SCREEN_RESTORE;
	}

	else {
		handleCharacterScreenAction(c, g);
	}
}

/**
 * Function to handle character screen action.
 */
void handleCharacterScreenAction(CharacterScreen* c, Game* g) {
	
}

/**
 * Function to check if the closed button was clicked.
 */
int checkClosedClicked(CharacterScreen* c, Mouse* m) {
	MenuOption* mo = c->closeOpt;

	if((m->mPos.x >= mo->left) && (m->mPos.x <= mo->right) && (m->mPos.y >= mo->top) && (m->mPos.y <= mo->bottom)) {
		return 1;
	}

	return 0;
}