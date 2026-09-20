/**
 * Mouse.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement mouse related functions.
 */

 #include "HEADER/MOUSE.H"
 #include "HEADER/SCREEN.H"
 #include "HEADER/GAME.H"
 #include "HEADER/GSTATE.H"
 #include <GRX20.H>
 #include <stdlib.h>

 /**
  * Function to initialize the mouse.
  */
 Mouse* initMouse(Screen* s) {
	Mouse* m = malloc(sizeof *m);

	m->enabled = 0;
	m->mPos.x = (s->width / 2);
	m->mPos.y = (s->height / 2);

	return m;
 }

 /**
  * Function to destroy the mouse.
  */
 void destroyMouse(Mouse* m) {
	//Free the mouse
	free(m);
 }

 /**
  * Function to enable the mouse.
  */
 void enableMouse(Mouse* m, Screen* s) {
	if(GrMouseDetect()) {
        GrMouseInit();

        //Use this to stop the mouse input from eating keyboard input
        GrMouseEventEnable(0, 1);

        GrMouseSetLimits(0, 0, s->width - 1, s->height - 1);

		GrMouseWarp(m->mPos.x, m->mPos.y);

		//Erase the cursor, since we will use our own
		GrMouseEraseCursor();

		//Set the mouse as enabled
		m->enabled = 1;
    }
 }

/**
  * Function to disable the mouse.
  */
 void disableMouse(Mouse* m) {
	if(m->enabled) {
		//Disable the mouse
		GrMouseEraseCursor();
		GrMouseUnInit();
		m->enabled = 0;
	}
 }

/**
  * Function to process the mouse input.
  */
 void processMouseInput(Mouse* m, Game* g, Screen* s) {
	//Variable for the mouse event
	GrMouseEvent ev;

	//Check to see if the mouse is enabled
	if(m->enabled == 0) {
		return;
	}

	//Check the mouse event
	while(GrMousePendingEvent()) {
		//Poll the event from the mouse
		GrMouseGetEvent(GR_M_MOTION | GR_M_BUTTON_CHANGE, &ev);

		//Check to see if the mouse has moved
		//Checked by logic AND
		if(ev.flags & GR_M_MOTION) {
			//The mouse moved and the location needs to be updated
			m->mPos.x = ev.x;
			m->mPos.y = ev.y;
		}

		//Check for left mouse button input
		if(ev.flags & GR_M_LEFT_DOWN) {
			g->state = EXIT_GAME;
		}

		//Check for right mouse button input
		if(ev.flags & GR_M_RIGHT_DOWN) {

		}
	}
 }

/**
  * Function to render the mouse cursor.
  */
 void renderMouseCursor(Mouse*m, Game* g, Screen* s) {
	//Get the locations for easy access
	Vec2 pos = m->mPos;

	/*
     * Black offset creates contrast against bright backgrounds.
     */
    GrLine(pos.x + 1, pos.y + 1, pos.x + 1, pos.y + 13, GrBlack());
    GrLine(pos.x + 1, pos.y + 1, pos.x + 10, pos.y + 10, GrBlack());
    GrLine(pos.x + 10, pos.y + 10, pos.x + 6, pos.y + 10, GrBlack());
    GrLine(pos.x + 6, pos.y + 10, pos.x + 9, pos.y + 16, GrBlack());

    /*
     * White cursor foreground.
     */
    GrLine(pos.x, pos.y, pos.x, pos.y + 12, GrWhite());
    GrLine(pos.x, pos.y, pos.x + 9, pos.y + 9, GrWhite());
    GrLine(pos.x + 9, pos.y + 9, pos.x + 5, pos.y + 9, GrWhite());
    GrLine(pos.x + 5, pos.y + 9, pos.x + 8, pos.y + 15, GrWhite());
 }