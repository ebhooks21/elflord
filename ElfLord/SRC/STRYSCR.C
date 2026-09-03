/**
 * Stryscr.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the story screen.
 */

#include "HEADER/STRYSCR.H"
#include "HEADER/SCREEN.H"
#include "HEADER/GAME.H"
#include <GRX20.H>
#include <stddef.h>

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
	if(((StoryScreen*)s->currScreen)->page == 1) {
		renderScreenText("50 years ago, the Elves turned on the other races", 7, 10, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("in an attempt to please their dark god Veldor.", 7, 19, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("They started a dark and bloody war that lasted", 7, 27, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("nearly 10 years, before the combined might of the", 7, 36, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("other races prevailed, pushing the Elven forces", 7, 45, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("back and vanquishing them until only a few", 7, 54, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("hundred remained.", 7, 63, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);

		
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
	}
	
	else {
		renderScreenText("He now travels from town to town, helping wherever", 7, 10, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("he may, hoping to one day free the world of the", 7, 19, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("evil his people brought upon it. He also seeks", 7, 27, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("to one day purify the Elves sacred aritifact, a", 7, 36, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("sword that he carries upon his back that will not", 7, 45, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("respond to call, instead remaining locked within", 7, 54, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("its sheath", 7, 63, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);

		renderScreenText("It is said that the veil blocking the Elves from", 7, 77, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("the outside world can be broken if the sword", 7, 86, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("can be purified, and then plunged deep within the", 7, 95, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
		renderScreenText("magical wall that makes up the veil...", 7, 104, GR_ALIGN_LEFT, GrBlack(), GrNOCOLOR, &GrFont_PC6x8);
	}

	if(((s->rCount / 120) % 2) == 0) {
			renderScreenText("PRESS ANY KEY TO CONTINUE...", ((int)(s->width / 2) + 6), 180, GR_ALIGN_CENTER, s->red, GrNOCOLOR, &GrFont_PC8x14);
	}
}
