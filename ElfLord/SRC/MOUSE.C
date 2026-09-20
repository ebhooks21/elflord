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

	//Set the previous position
	m->mPrevPos.x = m->mPos.x;
	m->mPrevPos.y = m->mPos.y;

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
		//Initialize the GRX mouse
        GrMouseInit();

		//Set the mouse sensitivity
		GrMouseSetSpeed(1, 8);
		GrMouseSetAccel(64, 1);

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

	do {
		//Poll the event from the mouse
		GrMouseGetEvent(GR_M_MOTION | GR_M_BUTTON_CHANGE | GR_M_POLL | GR_M_NOPAINT, &ev);

		//Check to see if the mouse has moved
		//Checked by logic AND
		if(ev.flags & GR_M_MOTION) {
			//The mouse moved and the location needs to be updated
			m->mPos.x = ev.x;
			m->mPos.y = ev.y;

			//Check the game state
			switch(g->state) {
				case GAMEPLAY:
					//Check to see if the mouse has moved left or right
					if(m->mPos.x != m->mPrevPos.x) {
						//Mouse has moved
						if(m->mPos.x < m->mPrevPos.x) {
							//Moved left
							rotatePlayer(g->p, -((g->p)->rotSpeed));
						}

						else {
							//Moved right
							rotatePlayer(g->p, ((g->p)->rotSpeed));
						}
					}
					break;
			}

			//Set the previous position
			m->mPrevPos.x = m->mPos.x;
			m->mPrevPos.y = m->mPos.y;
		}

		//Check for left mouse button input
		if(ev.flags & GR_M_LEFT_DOWN) {
			g->state = EXIT_GAME;
		}

		//Check for right mouse button input
		if(ev.flags & GR_M_RIGHT_DOWN) {

		}
	} while(ev.flags != 0);
 }

/**
  * Function to render the mouse cursor.
  */
 void renderMouseCursor(Mouse*m, Game* g, Screen* s) {
	//Get the locations for easy access
	int x = m->mPos.x;
	int y = m->mPos.y;	
	int numPoints = 0;

	//Create the cursor
	int cursor[][2] = {
		{x, y},
		{x, y + 9},
		{x + 2, y + 7},
		{x + 4, y + 10},
		{x + 6, y + 9},
		{x + 4, y + 6},
		{x + 7, y + 6}
	};

	switch(g->state) {
		case TITLE:
			//Calculate the number of points
			numPoints = (sizeof(cursor) / sizeof(cursor[0]));

			//Draw the cursor in the location
			GrFilledPolygon(numPoints, cursor, GrWhite());
			GrPolygon(numPoints, cursor, GrBlack());
			break;

		case GAMEPLAY:
			x = (s->width / 2);
			y = (s->height / 2);

			/* Small crosshair with a one-pixel center gap */
			GrLine(x - 3, y, x - 1, y, GrWhite());
			GrLine(x + 1, y, x + 3, y, GrWhite());
			GrLine(x, y - 3, x, y - 1, GrWhite());
			GrLine(x, y + 1, x, y + 3, GrWhite());

			//Reset the mouse cursor
			m->mPos.x = x;
			m->mPos.y = y;

			if(m->mPos.x <= 1 ) {
				m->mPos.x = (s->width - 1);
			}

			if(m->mPos.x >= s->width) {
				m->mPos.x = 2;
			}
			break;
	}

 }
