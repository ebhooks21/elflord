/**
 * Menuopt.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the menu option structure.
 */

 #include "VEC2.H"
 #include <GRX20.H>

 #ifndef MENUOPT_H
 #define MENUOPT_H

 typedef struct {
	//Variable for the menu option text
	char* text;

	//Variable for the text screen coordinate position
	Vec2 pos;

	//Variables for the width and height of the text
	int width;
	int height;

	//Variables for the text hit box
	int top;
	int right;
	int bottom;
	int left;

	//Variable for the text option
	GrTextOption* to;
 } MenuOption;

/**
 * Function to create a menu option.
 */
MenuOption* initMenuOption(char* t, int x, int y, GrTextOption *to);

/**
 * Function to destory a menu option.
 */
void destroyMenuOption(MenuOption* m);

/**
 * Function to render a menu option on the screen.
 */
void renderMenuOption(MenuOption* m, char* t);

 #endif