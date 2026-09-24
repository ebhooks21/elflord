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

/**
 * Function to initialize the title screen.
 */
TitleScreen* initTitleScreen(Screen* s) {
	TitleScreen* t = malloc(sizeof *t);

	//Load the background image
    t->background = GrCreateContext(s->width, s->height, NULL, NULL);
    GrLoadContextFromPnm(t->background, "ASSET\\title.ppm");

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

    //Write the menu options to the screen
    if(t->menuOption == 0) {
		sprintf(tempText, "> %s <", t->newGameText);
    }

    else {
		sprintf(tempText, "%s", t->newGameText);
    }

	renderScreenText(tempText, (int)(s->width / 2), (int)(s->height / 2), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);

    if(t->menuOption == 1) {
		sprintf(tempText, "> %s <", t->continueGameText);
    }

    else {
		sprintf(tempText, "%s", t->continueGameText);
    }

	renderScreenText(tempText, (int)(s->width / 2), ((int)(s->height / 2) + 32), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);

    if(t->menuOption == 2) {
		sprintf(tempText, "> %s <", t->returnToDosText);
    }

    else {
		sprintf(tempText, "%s", t->returnToDosText);
    }

	renderScreenText(tempText, (int)(s->width / 2), ((int)(s->height / 2) + 64), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
}