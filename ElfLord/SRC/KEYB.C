/**
 * File Name: KEYB.C
 * Author: Eric Hooks, 2026
 * Purpose: To implement key handling functions.
 */

 #include "HEADER/KEYB.H"
 #include "HEADER/GAME.H"
 #include <GRXKEYS.H>
 
/**
 * Function to handle title screen input.
 */
void handleTitleScreenKeyInput(Game* g, GrKeyType key) {
	if(key == GrKey_Return) {
		switch(g->menuOption) {
			case 0:
				g->state = GAME_START;
				break;
			
			case 2:
				g->state = EXIT_GAME;
				break;
		}
	}

	else if((key == GrKey_Up) && (g->menuOption > 0)) {
		g->menuOption--;
	}

	else if((key == GrKey_Down) && (g->menuOption < 2)) {
		g->menuOption++;
	}
}

/**
 * Function to handle generic input.
 */
void handleGenericKeyInput(Game* g, GrKeyType key) {
	if(key == GrKey_Escape) {
		g->state = EXIT_GAME;
	}
}

/**
 * Function to handle keypresses.
 */
void processKeyInput(Game* g) {
	GrKeyType key;

	if(GrKeyPressed() != 0) {
		key = GrKeyRead();

		switch(g->state) {
			case TITLE:
				handleTitleScreenKeyInput(g, key);
				break;

			default:
				handleGenericKeyInput(g, key);	
				break;
		}	
	}
}
