/**
 * File Name: KEYB.C
 * Author: Eric Hooks, 2026
 * Purpose: To implement key handling functions.
 */

 #include "HEADER/KEYB.H"
 #include "HEADER/GAME.H"
 #include "HEADER/SCREEN.H"
 #include "HEADER/STRYSCR.H"
 #include "HEADER/TITLESCR.H"
 #include "HEADER/CHARSCR.H"
 #include <GRXKEYS.H>
 #include <stdlib.h>
 
/**
 * Function to handle title screen input.
 */
void handleTitleScreenKeyInput(Game* g, GrKeyType key) {
	TitleScreen* t = (TitleScreen*)(g->screen)->currScreen;

	if(key == GrKey_Return) {
		handleTitleScreenAction(t, g);	
	}

	else if((key == GrKey_Up) && (t->menuOption > 0)) {
		t->menuOption--;
	}

	else if((key == GrKey_Down) && (t->menuOption < 2)) {
		t->menuOption++;
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
 * Function to handle story screen input.
 */
void handleStoryScreenKeyInput(Game* g, GrKeyType key) {
	StoryScreen* s = (StoryScreen*) (g->screen)->currScreen;

	handleStoryScreenAction(s, g);
}

/**
 * Function to handle the game play screen input.
 */
void handleGameplayScreenKeyInput(Game* g, GrKeyType key) {
	switch(key) {
		case GrKey_Up:
		case 'w':
		case 'W':
			movePlayer(g, (g->p)->moveSpeed);
			break;

		case GrKey_Down:
		case 's':
		case 'S':
			movePlayer(g, -((g->p)->moveSpeed));
			break;

		case GrKey_Left:
		case 'a':
		case 'A':
			rotatePlayer(g->p, -((g->p)->rotSpeed));
			break;

		case GrKey_Right:
		case 'd':
		case 'D':
			rotatePlayer(g->p, (g->p)->rotSpeed);
			break;

		case 'c':
			//Need to swap to the character screen
			g->state = CHARACTER_SCREEN_INIT;
			break;

		case GrKey_Escape:
			g->state = EXIT_GAME;
			break;
	}	
}

/**
 * Function to handle the character screen input.
 */
void handleCharacterScreenKeyInput(Game*g, GrKeyType key) {
	CharacterScreen* cs = (CharacterScreen*)(g->screen)->currScreen;

	switch(key) {
		case GrKey_Tab:
			//Cycle between the character screen views
			if(cs->state < 3) {
				cs->state++;
			}

			else {
				cs->state = CHARACTER_SHEET;
			}
			break;
		case GrKey_Escape:
			//Restore the gameplay screen
			g->state = GAMEPLAY_SCREEN_RESTORE;
			break;
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

			case STORY_SCREEN:
				handleStoryScreenKeyInput(g, key);
				break;

			case GAMEPLAY:
				handleGameplayScreenKeyInput(g, key);
				break;

			case CHARACTER_SCREEN:
				handleCharacterScreenKeyInput(g, key);
				break;

			default:
				handleGenericKeyInput(g, key);	
				break;
		}	
	}
}
