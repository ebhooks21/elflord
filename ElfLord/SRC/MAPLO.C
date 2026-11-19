/**
 * Maplo.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the map loader.
 */

 #include "HEADER/MAPLO.H"
 #include "HEADER/MAP.H"
 #include "HEADER/MCELL.H"
 #include "HEADER/MCELLTYP.H"
 #include "HEADER/ENTITY.H"
 #include "HEADER/ENTTYP.H"
 #include "HEADER/ESPRITET.H"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>

/**
 * Function for loading a map.
 */
Map* loadMap(char* mapName) {
	char mapPath[50];
	char fBuffer[256];
	int line = 0;
	int mWidth = 0;
	int mHeight = 0;
	int currMapRow = 0;
	Map* lMap = NULL;

	//Setup the mapPath
	sprintf(mapPath, "ASSET\\MAPS\\%s.MAP", mapName);

	//Start loading data from the map file
	FILE *mFile = fopen(mapPath, "r");

	//Make sure the file opened
	if(mFile == NULL) {
		return lMap;
	}

	//Read in each line of the file
	while(fgets(fBuffer, sizeof(fBuffer), mFile) != NULL) {
		//Increment the line number
		line++;

		//Check to see if we are on the first line
		if(line == 1) {
			parseMapWidthHeight(fBuffer, &mWidth, &mHeight);

			//Create the map using the values
			lMap = initMap(mHeight, mWidth);
		}

		if(line == 2) {
			//Discard line 2, as it should be blank
		}

		//Starting at line 3, read the map until the height line
		if((line > 2) && (line < ((lMap->mapRows) + 3))) {
			//Parse the map line
			buildMapRow(lMap, fBuffer, currMapRow);

			//Increment the current map row
			currMapRow++;
		}

		if(line == ((lMap->mapRows) + 4)) {
			fBuffer[strcspn(fBuffer, "\n")] = '\0';

			//Load the floor texture path
			lMap->fTexPath = dupStr(fBuffer);
		}

		if(line == ((lMap->mapRows) + 5)) {
			fBuffer[strcspn(fBuffer, "\n")] = '\0';

			//Load the ceiling texture path
			lMap->cTexPath = dupStr(fBuffer);
		}
		
		if(line == ((lMap->mapRows) + 6)) {
			fBuffer[strcspn(fBuffer, "\n")] = '\0';

			//Load the wall texture path
			lMap->wTexPath = dupStr(fBuffer);
		}

		if(line == ((lMap->mapRows) + 7)) {
			fBuffer[strcspn(fBuffer, "\n")] = '\0';

			//Load the wall texture path
			lMap->dTexPath = dupStr(fBuffer);
		}
	}

	//Add random entities to map
	//Remove this after the game jam
	addRandomEntities(lMap);

	//Return the map
	return lMap;
}

/**
 * Function to parse the map width and height.
 */
void parseMapWidthHeight(char* fBuffer, int* width, int* height) {
	char* tChar;

	//Split the buffer by a space, then compute H W
	tChar = strtok(fBuffer, " ");

	if(tChar != NULL) {
		*height = atoi(tChar);
	}

	tChar = strtok(NULL, " ");

	if(tChar != NULL) {
		*width = atoi(tChar);
	}
}

/**
 * Function to build the map row.
 */
void buildMapRow(Map* map, char* fBuffer, int currRow) {
	char* tChar;

	for(int i = 0; i < map->mapCols; i++) {
		//Split on the buffer if this is the first Split
		if(i == 0) {
			tChar = strtok(fBuffer, ",");
		}

		//Else, split on NULL which uses the currently loaded buffer
		else {
			tChar = strtok(NULL, ",");
		}

		//Make sure there is data
		if(tChar != NULL) {
			if(*tChar == '@') {
				//Player starting position
				map->pStart.x = i;
				map->pStart.y = currRow;
			}

			if(*tChar == 'G') {
				//Gold on the map
				addEntityToMap(map, initEntity(E_ITEM, (i + 0.5f), (currRow + 0.5f), 0.5, I_GOLD));
			}

			map->mapData[currRow][i] = initMapCell(*tChar);
		}
	}
}

/**
 * Function to duplicate a string.
 */
char* dupStr(char* s) {
	int length = 0;
	char* ns;

	if(s == NULL) {
		return s;
	}

	length = strlen(s) + 1;
	ns = malloc(length);

	if(ns != NULL) {
		memcpy(ns, s, length);
	}

	return ns;
}

/**
 * Add random entities to the map.
 */
void addRandomEntities(Map* map) {
	Vec2 ePos;
	Entity* e;
	int maxEntitiesToPlace = 10;
	int makingEntity = 1;
	int entityFound = 0;
	int eType = 0;

	for(int i = maxEntitiesToPlace; i > 0; i--) {
		//Loop until we create an entity
		makingEntity = 1;
		while(makingEntity) {
			entityFound = 0;
			ePos.x = (rand() % map->mapCols);
			ePos.y = (rand() % map->mapRows);

			if((((ePos.x <= (map->pStart.x + 2)) && (ePos.y <= (map->pStart.y + 2))))) {
				if((map->mapData[ePos.y][ePos.x])->cType == M_CELL_EMPTY) {
					//The random cell is an empty cell, check for an entity
					for(int j = 0; j < map->numEntites; j++) {
						e = map->entities[j];

						if(e != NULL) {
							if((((e->ePos.x - 0.5f) == ePos.x) && ((e->ePos.y - 0.5f) == ePos.y))) {
								entityFound = 1;
								break;
							}
						}
					}

					if(!entityFound) {
						//Determine the type of entity
						eType = (rand() % 10);
						
						if(eType < 5) {
							map->numGold++;
							addEntityToMap(map, initEntity(E_ITEM, (ePos.x + 0.5f), (ePos.y + 0.5f), 0.5, I_GOLD));
						}

						else {
							addEntityToMap(map, initEntity(E_ENEMY, (ePos.x + 0.5f), (ePos.y + 0.5f), 0.7, E_SKELETON));
						}
						makingEntity = 0;
					}
				}	
			}
		}
	}
}
