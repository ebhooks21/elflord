/**
 * Mouse.h
 * Author: Eric Hooks, 2026
 * Purpose: To track and control mouse functions.
 */

 #include <GRX20.H>
 #include "VEC2.H"

 //Forward declare the screen structure
 typedef struct screen_t Screen;

 //Forward declare the game structure
 typedef struct game_t Game;

 #ifndef MOUSE_H
 #define MOUSE_H

 //Define the mouse structure
 typedef struct {
	//Variable for if the mouse is enabled
	int enabled;

	//Variable for the mouse position
	Vec2 mPos;
 } Mouse;

 /**
  * Function to initialize the mouse.
  */
 Mouse* initMouse(Screen* s);

 /**
  * Function to destroy the mouse.
  */
 void destroyMouse(Mouse* m);

 /**
  * Function to enable the mouse.
  */
 void enableMouse(Mouse* m, Screen* s);

 /**
  * Function to disable the mouse.
  */
 void disableMouse(Mouse* m);

 /**
  * Function to process the mouse input.
  */
 void processMouseInput(Mouse* m, Game* g, Screen* s);

 /**
  * Function to render the mouse cursor.
  */
 void renderMouseCursor(Mouse*m, Game* g, Screen* s);

 #endif