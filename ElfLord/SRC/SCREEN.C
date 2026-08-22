/**
 * Screen.c
 * Author: Eric Hooks
 * Purpose: To implement the screen functions.
 */
#include "HEADER/SCREEN.H"
#include "HEADER/GAME.H"
#include <GRX20.H>
#include <stdio.h>
#include <string.h>

/**
 * Function to initialize the screen.
 */
void initScreen(Screen* s) {
	//Set the graphics mode to 640x480 with 256 colors
    GrSetMode(GR_width_height_color_graphics, s->width, s->height, 256);
    GrSetRGBcolorMode();

    //Preset the context
    s->sContext = GrScreenContext();
}

/**
 * Function to destroy the screen.
 */
void destroyScreen(Screen* s) {
    //Delete the background context if it hasnt been already
    if(s->background != NULL) {
        GrDestroyContext(s->background);
        s->background = NULL;
    }

	//Reset the video mode
    GrSetMode(GR_default_text);
}

/**
 * Function to draw the screen border.
 */
void drawScreenBorder(Screen* s) {
    GrBox(0, 0, GrMaxX(), GrMaxY(), GrWhite());
}

/**
 * Function to render the shop status area.
 */
void renderStatusBar(Screen* s, Game* g) {
    char money[10];

    //Draw the border for the money area
    GrBox(0, 0, ((int)(GrMaxX() / 4) - 1), 35, GrWhite()); 

    //Draw the money amount
    GrTextXY(2, 12, money, GrWhite(), GrBlack());
}

/**
 * Function to render the title screen.
 */
void renderTitleScreen(Screen* s, int menuOption) {
    if(s->background == NULL) {
        //Load the background image into memory
        s->background = GrCreateContext(s->width, s->height, NULL, NULL);
        GrLoadContextFromPnm(s->background, "ASSET\\title.ppm");
    }

    //Write the background image
    GrBitBlt(s->sContext, 0, 0, s->background, 0, 0, (s->width - 1), (s->height - 1), GrWRITE);

    //Write the menu options to the screen
    if(menuOption == 0) {
        renderScreenText("[ New Game ]", (int)(s->width / 2), (int)(s->height / 2), GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }

    else {
        renderScreenText("New Game", (int)(s->width / 2), (int)(s->height / 2), GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }

    if(menuOption == 1) {
        renderScreenText("[ Continue ]", (int)(s->width / 2), ((int)(s->height / 2) + 32), GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }

    else {
        renderScreenText("Continue", (int)(s->width / 2), ((int)(s->height / 2) + 32), GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }

    if(menuOption == 2) {
        renderScreenText("[ Return to DOS ]", (int)(s->width / 2), ((int)(s->height / 2) + 64), GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }

    else {
        renderScreenText("Return to DOS", (int)(s->width / 2), ((int)(s->height / 2) + 64), GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }
}

/**
 * Function to render screen text.
 */
void renderScreenText(char* t, int x, int y, GrColor fc, GrColor bc, GrFont* fnt) {
    GrTextOption options;

    options.txo_font = fnt;
    options.txo_fgcolor.v = fc;
    //options.txo_bgcolor.v = GrNOCOLOR;
    options.txo_bgcolor.v = bc;
    options.txo_chrtype = GR_BYTE_TEXT;
    options.txo_direct = GR_TEXT_RIGHT;
    options.txo_xalign = GR_ALIGN_CENTER;
    options.txo_yalign = GR_ALIGN_TOP;

    GrDrawString(
        (void *)t,
        strlen(t),
        x,
        y,
        &options
    );
}

/**
 * Function to render the game screen.
 */
void render(Screen* s, Game* g) {
    //See what we need to render
    switch(g->state) {
        case TITLE:
            renderTitleScreen(s, g->menuOption);
            break;

        default:
            GrClearScreen(GrBlack());
            break;
    }
}