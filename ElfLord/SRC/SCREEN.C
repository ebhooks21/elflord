/**
 * Screen.c
 * Author: Eric Hooks
 * Purpose: To implement the screen functions.
 */
#include "HEADER/SCREEN.H"
#include "HEADER/GAME.H"
#include <GRX20.H>
#include <stdio.h>

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
void renderTitleScreen(Screen* s) {
    if(s->background == NULL) {
        //Load the background image into memory
        s->background = GrCreateContext(s->width, s->height, NULL, NULL);
        GrLoadContextFromPnm(s->background, "ASSET\\title.ppm");
    }

    GrBitBlt(s->sContext, 0, 0, s->background, 0, 0, (s->width - 1), (s->height - 1), GrWRITE);
}

/**
 * Function to render the game screen.
 */
void render(Screen* s, Game* g) {
    //See what we need to render
    switch(g->state) {
        case TITLE:
            renderTitleScreen(s);
            break;

        default:
            GrClearScreen(GrBlack());
            break;
    }
}