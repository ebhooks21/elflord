/**
 * Screen.c
 * Author: Eric Hooks
 * Purpose: To implement the screen functions.
 */
#include "HEADER/SCREEN.H"
#include "HEADER/GAME.H"
#include "HEADER/GSTATE.H"
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

    //Setup the colors
    s->red = GrAllocColor(255, 0, 0);

    //Preset the context
    s->sContext = GrScreenContext();

    //Off-screen back buffer
    s->frame = GrCreateContext(s->width, s->height, NULL, NULL);

    //Zero the render count
    s->rCount = 0;

    //Start drawing into the back buffer
    GrSetContext(s->frame);
}

/**
 * Function to destroy the screen.
 */
void destroyScreen(Screen* s) {
    //Delete the background context if it hasnt been already
    if(s->background != NULL) {
        unloadBackground(s);
    }

    if(s->frame != NULL) {
        GrDestroyContext(s->frame);
        s->frame = NULL;
    }

	//Reset the video mode
    GrSetMode(GR_default_text);
}

/**
 * Function to draw the screen border.
 */
void drawScreenBorder(Screen* s, GrColor c) {
    GrBox(0, 0, GrMaxX(), GrMaxY(), c);
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
        loadBackground(s, "ASSET\\title.ppm");
    }

    //Write the background image
    GrBitBlt(s->frame, 0, 0, s->background, 0, 0, (s->width - 1), (s->height - 1), GrWRITE);

    //Write the menu options to the screen
    if(menuOption == 0) {
        renderScreenText("> New Game <", (int)(s->width / 2), (int)(s->height / 2), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }

    else {
        renderScreenText("New Game", (int)(s->width / 2), (int)(s->height / 2), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }

    if(menuOption == 1) {
        renderScreenText("> Continue <", (int)(s->width / 2), ((int)(s->height / 2) + 32), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }

    else {
        renderScreenText("Continue", (int)(s->width / 2), ((int)(s->height / 2) + 32), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }

    if(menuOption == 2) {
        renderScreenText("> Return to DOS <", (int)(s->width / 2), ((int)(s->height / 2) + 64), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }

    else {
        renderScreenText("Return to DOS", (int)(s->width / 2), ((int)(s->height / 2) + 64), GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC8x16);
    }
}

/**
 * Function to render screen text.
 */
void renderScreenText(char* t, int x, int y, int align, GrColor fc, GrColor bc, GrFont* fnt) {
    GrTextOption options;

    options.txo_font = fnt;
    options.txo_fgcolor.v = fc;
    //options.txo_bgcolor.v = GrNOCOLOR;
    options.txo_bgcolor.v = bc;
    options.txo_chrtype = GR_BYTE_TEXT;
    options.txo_direct = GR_TEXT_RIGHT;
    options.txo_xalign = align;
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
     //Draw into the off-screen frame
    GrSetContext(s->frame);
    GrClearContext(GrBlack());

    //See what we need to render
    switch(g->state) {
        case TITLE:
            renderTitleScreen(s, g->menuOption);
            break;

        case STORY_SCREEN:
            renderStoryScreen(s, g);
            break;

        default:
            GrClearScreen(GrBlack());
            break;
    }

    GrBitBlt(s->sContext, 0, 0, s->frame, 0, 0, (s->width - 1), (s->height - 1), GrWRITE);

    //Increment the render count
    s->rCount++;
}

/**
 * Function to unload the background.
 */
void unloadBackground(Screen* s) {
    GrDestroyContext(s->background);
    s->background = NULL;
}

/**
 * Function to load a background.
 */
void loadBackground(Screen* s, char* backgroundPath) {
    //Load the background image into memory
    s->background = GrCreateContext(s->width, s->height, NULL, NULL);
    GrLoadContextFromPnm(s->background, backgroundPath);
}

/**
 * Function to render the story screen.
 */
void renderStoryScreen(Screen* s, Game* g) {
    if(s->background == NULL) {
        //Load the background image into memory
        loadBackground(s, "ASSET\\paper.ppm");
    }

    //Write the background image
    GrBitBlt(s->frame, 0, 0, s->background, 0, 0, (s->width - 1), (s->height - 1), GrWRITE);

    //Write the text to the screen
    renderScreenText("50 years ago, the Elves turned on the other races", 7, 10, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("in an attempt to please their dark god Veldor.", 7, 19, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("They started a dark and bloody war that lasted", 7, 27, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("nearly 10 years, before the combined might of the", 7, 36, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("other races prevailed, pushing the Elven forces", 7, 45, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("back and vanquishing them until only a few", 7, 54, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("until only a few hundred remained.", 7, 63, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);

    
    renderScreenText("Beaten and on the edge of extinction, the", 7, 77, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("Elves hid themselves away in a distant valley", 7, 86, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("and surrendered. Angered by this, Veldor took", 7, 95, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("vengence against his worshippers, putting a", 7, 104, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("dark and impenetrable veil between his people", 7, 113, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("and the world, while tainting thier most sacred", 7, 122, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("artifact. Luckily, a single elf was left outside", 7, 131, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("the veil. For the last 40 years, he has wandered", 7, 140, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("the world, attempting to right the wrongs of his", 7, 149, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    renderScreenText("people while hiding his own true identity.", 7, 158, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
    
    if(((s->rCount / 80) % 2) == 0) {
        renderScreenText("PRESS ANY KEY TO CONTINUE...", ((int)(s->width / 2) + 6), 180, GR_ALIGN_CENTER, s->red, GrNOCOLOR, &GrFont_PC8x14);
    }
}
