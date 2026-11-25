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
 #include "HEADER/CCSCR.H"
 #include "HEADER/MCELL.H"
 #include "HEADER/MCELLTYP.H"
 #include "HEADER/MAP.H"
 #include "HEADER/ENTTYP.H"
 #include "HEADER/ENTITY.H"
 #include "HEADER/ENEMY.H"
 #include "HEADER/ITEM.H"
 #include "HEADER/HELPSCR.H"
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
	Entity* e = NULL;
	MapCell* mc = NULL;
	Item* item = NULL;
	Enemy* enemy = NULL;

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

		case GrKey_F1:
			//Help screen
			g->state = HELP_SCREEN_INIT;
			break;

		case 'c':
			//Need to swap to the character screen
			g->state = CHARACTER_SCREEN_INIT;
			break;

		case 'e':
			//Find out if the player is near an entity
			e = checkPlayerProximity(g->currMap, g->p);

			if(e != NULL) {
				switch(e->type) {
					case E_ITEM:
						//Check the item type by sprite type(only for now)
						switch(e->spriteType) {
							case I_GOLD:
								//Get the item
								item = e->ent.item;

								//Temporarily track the bags of gold
								(g->currMap)->numGold--;

								//Give item to the player
								givePlayerItem(g->p, g, item);

								//Mark the entity as inactive
								e->active = 0;
								break;

							case I_HEALTH:
								(g->p)->currHP += 30;

								if((g->p)->currHP > (g->p)->maxHP) {
									(g->p)->currHP = (g->p)->maxHP;
								}

								e->active = 0;
								break;

							default:
								break;
						}
						break;

					default:
						break;
				}
			}

			else {
				//Check to see what they are looking at
				mc = checkPlayerLookingAt(g->currMap, g->p);

				if(mc != NULL) {
					switch(mc->cType) {
						case M_CELL_DOOR:
							if((g->currMap)->numGold <= 0) {
								//The player is leaving the dungeon
								g->state = SUCCESS_SCREEN_INIT;
							}
							break;

						default:
							break;
					}
				}
			}
			break;

		case GrKey_Escape:
			//Change to the close confirmation screen
			g->state = EXIT_PROMPT_INIT;
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
 * Function to handle close confirmation screen input.
 */
void handleCloseConfirmationScreenKeyInput(Game* g, GrKeyType key) {
	switch(key) {	
		case 'y':
		case 'Y':
			g->state = EXIT_GAME;
			break;

		case 'n':
		case 'N':
			//Restore the gameplay screen
			g->state = EXIT_PROMPT_CLOSE;
			break;

		case GrKey_Escape:
			//Restore the gameplay screen
			g->state = EXIT_PROMPT_CLOSE;
			break;
	}
}

/**
 * Function to handle success screen input.
 */
void handleSuccessScreenKeyInput(Game* g, GrKeyType key) {
	//Go immediately to exit
	g->state = EXIT_GAME;
}

/**
 * Function to handle help screen input.
 */
void handleHelpScreenKeyInput(Game* g, GrKeyType key) {
	switch(key) {
		case GrKey_Escape:
			//Restore the gameplay screen
			g->state = HELP_SCREEN_CLOSE;
			break;
	}
}

/**
 * Function to handle death screen input.
 */
void handleDeathScreenKeyInput(Game* g, GrKeyType key) {
	switch(key) {
		default:
			//Exit the game
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

			case CHARACTER_SCREEN:
				handleCharacterScreenKeyInput(g, key);
				break;

			case EXIT_PROMPT:
				handleCloseConfirmationScreenKeyInput(g, key);
				break;

			case SUCCESS_SCREEN:
				handleSuccessScreenKeyInput(g, key);
				break;

			case HELP_SCREEN:
				handleHelpScreenKeyInput(g, key);
				break;

			case DEATH_SCREEN:
				handleDeathScreenKeyInput(g, key);
				break;

			default:
				handleGenericKeyInput(g, key);	
				break;
		}	
	}
}
