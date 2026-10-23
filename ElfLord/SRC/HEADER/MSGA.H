/**
 * Msga.h
 * Author: Eric Hooks, 2026
 * Purpose: To define the message area.
 */

#include "SCREEN.H"

#ifndef MSGA_H
#define MSGA_H

typedef struct {
	//Array of messages
	char msgs[5][30];

	//Variable for the number of messages
	int numMsgs;
} MessageArea;

/**
 * Function to add a message to the message area.
 */
void addMessage(MessageArea* m, char* msg);

/**
 * Function to render the message area.
 */
void renderMessageArea(MessageArea* m, Screen* s);

#endif