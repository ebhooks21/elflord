/**
 * Msga.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the Message Area.
 */
#include "HEADER/GAME.H"
#include "HEADER/MSGA.H"
#include "HEADER/SCREEN.H"
#include <GRX20.H>
#include <string.h>

/**
 * Function to add a message to the message area.
 */
void addMessage(MessageArea* m, char* msg) {
	//Check to see if the message area is full
	if(m->numMsgs == 4) {
		//Remove the first message and shift
		for(int i = 0; i < 4; i++) {
			//Shift each row up, overwriting the top
			strcpy(m->msgs[i], m->msgs[i + 1]);
		}

		//Put the newest message in the array
		strcpy(m->msgs[3], msg);
	}

	else {
		//Append the message and increment
		strcpy(m->msgs[m->numMsgs],msg); 
		m->numMsgs++;
	}
}

/**
 * Function to render the message area.
 */
void renderMessageArea(MessageArea* m, Screen* s, GamePlayScreen* gps) {
	int renderY = gps->gAreaHeight + 4;

	for(int i = 0; i < m->numMsgs; i++) {
		renderScreenText(m->msgs[i], 185, renderY, GR_ALIGN_LEFT, GrWhite(), GrNOCOLOR, &GrFont_PC6x8);
		renderY += 8;
	}
}
