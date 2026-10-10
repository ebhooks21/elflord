/**
 * Charscr.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the character screen.
 */
#include "HEADER/CHARSCR.H"
#include "HEADER/GAME.H"
#include "HEADER/SCREEN.H"
#include "HEADER/MENUOPT.H"
#include "HEADER/GIMAGE.H"
#include <GRX20.H>
#include <stdlib.h>
#include <stdio.h>

/**
 * Function to initialize the character screen.
 */
CharacterScreen* initCharacterScreen(Screen* s) {
	CharacterScreen* c = malloc(sizeof *c);

	//Load the screen background
	c->background = createGameImage("ASSET\\paper.ppm", 0, 0);
	loadGameImage(c->background);

	//Load the chracter portrait
	c->cPortrait = createGameImage("ASSET\\desryn.ppm", 0, 0);
	loadGameImage(c->cPortrait);

	//Create the active menu item color
	c->actMenuColor = GrAllocColor(255, 0, 0);

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
	destroyGameImage(c->background);

	//Destroy the character portrait
	destroyGameImage(c->cPortrait);

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
    GrBitBlt(s->frame, 0, 0, (c->background)->image, 0, 0, ((c->background)->width - 1), ((c->background)->height - 1), GrWRITE);

	//Render elements that are always on the screen, no matter the state
	//Render the menu options
	for(int i = 0; i < 4; i++) {
		if(c->state == i) {
			(c->mOpt[i])->to->txo_fgcolor.v = c->actMenuColor;
			(c->mOpt[i])->to->txo_font = &GrFont_PC8x8;
		}

		else {
			(c->mOpt[i])->to->txo_fgcolor.v = GrBlack();
			(c->mOpt[i])->to->txo_font = &GrFont_PC6x8;
		}

		renderMenuOption(c->mOpt[i], NULL);
	}

	//Render the close button
	renderMenuOption(c->closeOpt, NULL);

	//Render the subscreen based upon the state
	switch(c->state) {
		case CHARACTER_SHEET:
			//Render the character portrait
			GrBitBlt(s->frame, 20, 30, (c->cPortrait)->image, 0, 0, ((c->cPortrait)->width - 1), ((c->cPortrait)->height - 1), GrWRITE);

			//Render player information
			Player* p = g->p;

			renderScreenText(p->name, 100, 30, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC8x8);

			sprintf(tempText, "Level: %d", p->level);
			renderScreenText(tempText, 100, 40, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC8x8);

			sprintf(tempText, "Strength: %d", (p->stat).str);
			renderScreenText(tempText, 100, 50, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC8x8);
			
			sprintf(tempText, "Intelligence: %d", (p->stat).intel);
			renderScreenText(tempText, 100, 60, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC8x8);
			
			sprintf(tempText, "Dexterity: %d", (p->stat).dex);
			renderScreenText(tempText, 100, 70, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC8x8);
			
			sprintf(tempText, "Constitution: %d", (p->stat).con);
			renderScreenText(tempText, 100, 80, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC8x8);
			
			sprintf(tempText, "Luck: %d", (p->stat).luck);
			renderScreenText(tempText, 100, 90, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC8x8);
			
			sprintf(tempText, "Current Exp: %d", (p->stat).currExp);
			renderScreenText(tempText, 100, 100, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC8x8);
			
			sprintf(tempText, "Next Exp: %d", (p->stat).nextExp);
			renderScreenText(tempText, 100, 110, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC8x8);
			
			sprintf(tempText, "Total Exp: %d", (p->stat).totalExp);
			renderScreenText(tempText, 100, 120, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC8x8);
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
	c->mOpt[1] = initMenuOption("Inventory", ((c->mOpt[0])->pos.x + ((c->mOpt[0]->width)) + 25), 8, options);

	//Create the menu option for return to dos
	c->mOpt[2] = initMenuOption("Equipment", ((c->mOpt[1])->pos.x + ((c->mOpt[1]->width)) + 25), 8, options);
	
	//Create the menu option for return to dos
	c->mOpt[3] = initMenuOption("Spells", ((c->mOpt[2])->pos.x + ((c->mOpt[2]->width)) + 10), 8, options);
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
	MenuOption* mo = NULL; 

	if(checkClosedClicked(c, m)) {
		//Restore the gameplay screen
		g->state = GAMEPLAY_SCREEN_RESTORE;
	}

	else {
		//handleCharacterScreenAction(c, g);

		//Check to see which option might have been clicked
		for(int i = CHARACTER_SHEET; i <= SPELLS; i++) {
			mo = c->mOpt[i];

			if((m->mPos.x >= mo->left) && (m->mPos.x <= mo->right) && (m->mPos.y >= mo->top) && (m->mPos.y <= mo->bottom)) {
				c->state = i;
				break;
			}
		}
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