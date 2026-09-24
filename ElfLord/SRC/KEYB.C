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
 #include <GRXKEYS.H>
 #include <stdlib.h>
 
/**
 * Function to handle title screen input.
 */
void handleTitleScreenKeyInput(Game* g, GrKeyType key) {
	TitleScreen* t = (TitleScreen*)(g->screen)->currScreen;

	if(key == GrKey_Return) {
		switch(t->menuOption) {
			case 0:
				g->state = GAME_START_NEW;
				break;
			
			case 2:
				g->state = EXIT_GAME;
				break;
		}
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
	StoryScreen* ss = (StoryScreen*) (g->screen)->currScreen;

	if(ss->page == 2) {	
		//This will accept any key, so just change state
		g->state = INIT;
	}

	else {
		ss->page++;
	}
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

			case GrKey_Escape:
				g->state = EXIT_GAME;
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

			default:
				handleGenericKeyInput(g, key);	
				break;
		}	
	}
}
