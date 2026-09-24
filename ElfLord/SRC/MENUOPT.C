/**
 * Menuopt.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the menu option functions.
 */
#include "HEADER/MENUOPT.H"
#include "HEADER/VEC2.H"
#include <GRX20.H>
#include <string.h>
#include <stdlib.h>

/**
 * Function to create a menu option.
 */
MenuOption* initMenuOption(char* t, int x, int y, GrTextOption *to) {
	MenuOption* m = malloc(sizeof *m);
	int length;

	m->text = t;
	m->width = 0;
	m->height = 0;
	m->top = 0;
	m->right = 0;
	m->bottom = 0;
	m->left = 0;
	m->to = to;

	length = strlen(t);

	m->pos.x = x;
	m->pos.y = y;

	//Get the size of the string
	GrStringSize(m->text, length, m->to, &m->width, &m->height);

	m->top = y - (m->height / 2);
	m->right = x + (m->height / 2);
	m->bottom = y + (m->height / 2);
	m->left = x - (m->width / 2);

	return m;
}

/**
 * Function to destory a menu option.
 */
void destroyMenuOption(MenuOption* m) {
	free(m);
}

/**
 * Function to render a menu option on the screen.
 */
void renderMenuOption(MenuOption* m, char* t){
	if(t != NULL) {
		GrDrawString(t, strlen(t), m->pos.x, m->pos.y, m->to);
	}

	else {
		GrDrawString(m->text, strlen(m->text), m->pos.x, m->pos.y, m->to);
	}
}