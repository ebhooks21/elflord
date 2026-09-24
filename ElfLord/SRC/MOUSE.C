/**
 * Mouse.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement mouse related functions.
 */

 #include "HEADER/MOUSE.H"
 #include "HEADER/SCREEN.H"
 #include "HEADER/GAME.H"
 #include "HEADER/GSTATE.H"
 #include "HEADER/TITLESCR.H"
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

	//Set the center position
	m->mCenterPos.x = (s->width / 2);
	m->mCenterPos.y = (s->height / 2);

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
	int mouseMoved = 0;
	int mDeltaX = 0;
	int mDeltaY = 0;

	//Check to see if the mouse is enabled
	if(m->enabled == 0) {
		return;
	}

	do {
		//Poll the event from the mouse
		GrMouseGetEvent(GR_M_MOTION | GR_M_BUTTON_CHANGE | GR_M_POLL | GR_M_NOPAINT, &ev);

		//Check to see if the mouse has moved
		//Mouse movement is streamed, so we only need to take the last movement each time
		if(ev.flags & GR_M_MOTION) {
			//The mouse moved and the location needs to be updated
			m->mPos.x = ev.x;
			m->mPos.y = ev.y;	

			mouseMoved = 1;	
		}

		//Check for left mouse button input
		if(ev.flags & GR_M_LEFT_DOWN) {
			//Check the state	
			switch(g->state) {
				case TITLE:
					handleTitleScreenMouseLeftButtonInput((TitleScreen*)(g->screen)->currScreen, m, g);
				break;
			}
		}

		//Check for right mouse button input
		if(ev.flags & GR_M_RIGHT_DOWN) {

		}
	} while(ev.flags != 0);

	/**
	 * Check if mouse movement is registered and we are ni the gameplay screen
	 * This is becuase the gameplay screen force locks the map.
	 */
	if((g->state == GAMEPLAY) && mouseMoved) {
		//Calcuate the distance moved
		mDeltaX = m->mPos.x - m->mCenterPos.x;

		//Check to see if the mouse has moved left or right
		if(mDeltaX < 0) {
			//Moved left
			rotatePlayer(g->p, -((g->p)->rotSpeed));
		}

		else if(mDeltaX > 0) {
			//Moved right
			rotatePlayer(g->p, ((g->p)->rotSpeed));
		}

		//Warp the mouse back to center
		GrMouseWarp(m->mCenterPos.x, m->mCenterPos.y);

		//Reset the values
		m->mPrevPos = m->mPos;
		m->mPos.x = m->mCenterPos.x;
		m->mPos.y = m->mCenterPos.y;
	}

	//Movement for menus
	else if(mouseMoved) {
		m->mPos.x = ev.x;
		m->mPos.y = ev.y;	
		m->mPrevPos = m->mPos;

		//Check the state to see what event handler to use
		switch(g->state) {
			case TITLE:
				handleTitleScreenMouseMovement((TitleScreen*)(g->screen)->currScreen, m, g);
				break;
		}
	}
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
			break;
	}

 }
