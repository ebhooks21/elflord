/**
 * Gpscr.c
 * Author: Eric Hooks, 2026
 * Purpose: To implement the game play screen.
 */

 #include "HEADER/GPSCR.H"
 #include "HEADER/SCREEN.H"
 #include "HEADER/GAME.H"
 #include "HEADER/PLAYER.H"
 #include "HEADER/MAP.H"
 #include "HEADER/VEC2F.H"
 #include "HEADER/GIMAGE.H"
 #include "HEADER/GTEX.H"
 #include "HEADER/MCELL.H"
 #include "HEADER/MCELLTYP.H"
 #include "HEADER/TEXPROV.H"
 #include <GRX20.H>
 #include <stdlib.h>
 #include <stdio.h>
 #include <math.h>

/**
 * Function to initialize the gameplay screen.
 */
GamePlayScreen* initGPScr(Screen* s, Map* map) {
	GamePlayScreen* gps = malloc(sizeof *gps);

	gps->hAreaWidth = s->width;
	gps->hAreaHeight = 40; 
	gps->gAreaWidth = s->width - 1;
	gps->gAreaHeight = (s->height - gps->hAreaHeight);

	//Calculate horizon start line
	gps->horLine = gps->gAreaHeight / 2; //Horizon line is half the screen

	/**
	 * This is calculated based upon the idea that the player's viewpoint
	 * is roughly halfway up a single wall instance, which is equal to
	 * the view area height.
	 */
	gps->cHeight = (0.5 * (double)gps->gAreaHeight);

	//Load the hud background
	gps->hudBackground = createGameImage("ASSET\\hud.ppm", 0, 0);
	loadGameImage(gps->hudBackground);	

	//Create the framebuffer
	gps->frameBuffer = malloc(sizeof(GrColor) * gps->gAreaWidth * gps->gAreaHeight);

	//Create the z-buffer
	gps->zBuffer = malloc(sizeof(double) * gps->gAreaWidth);

	return gps;
}

/**
 * Function to destroy the gameplay screen.
 */
void destoryGPScr(GamePlayScreen* g) {
	//Destroy the textures
	destroyGameImage(g->hudBackground);	

	//Free the framebuffer
	free(g->frameBuffer);

	//Free the z-buffer
	free(g->zBuffer);

	//Destroy the gameplay screen
	free(g);
}

/**
 * Function to render the game play screen.
 */
void renderGameplayScreen(Screen* s, Game* g) {
	//Render the gameplay area
	renderGameplayArea(s, g);

	//Draw the hud area
	renderHudArea(s, g);
}

/**
 * Function to render the floor.
 */
void renderFloor(Screen* s, Game* g, GamePlayScreen* gps) {
	Player* p = g->p;
	TextureProvider* tp = (g->currMap)->texP;

	//Variables needed for floor cells
	gps->cellPos.x = 0;
	gps->cellPos.y = 0;
	gps->texPos.x = 0;
	gps->texPos.y = 0;
	int textureWidth = 0;
	int textureHeight = 0;
	double leftRayDirX = 0.0;
	double leftRayDirY = 0.0;
	double rightRayDirX = 0.0;
	double rightRayDirY = 0.0;

	double rowDistance = 0.0;
	double floorStepX = 0.0;
	double floorStepY = 0.0;
	double floorX = 0.0;
	double floorY = 0.0;
	double fractionX = 0.0;
	double fractionY = 0.0;

	int row = 0; //Row needed for floor casting
	int x = 0; //X postion needed for floor casting

	//Framebuffer line
	GrColor* line;
	
	//Calculate the floor texture sizes
	textureWidth = (tp->floorTexture)->width;
	textureHeight = (tp->floorTexture)->height;

	//Calculate the values for the left and right camera edges
	leftRayDirX = gps->rDir.x - gps->pViewPlane.x;
	leftRayDirY = gps->rDir.y - gps->pViewPlane.y;
	rightRayDirX = gps->rDir.x + gps->pViewPlane.x;
	rightRayDirY = gps->rDir.y + gps->pViewPlane.y;

	//Cast and draw the floor below the horizon
	//Make sure we have the floor texture and sizes
	if((gps->frameBuffer != NULL) && (textureWidth > 0) && (textureHeight > 0)) {
		//Loop through the row
		for(row = (gps->horLine + 1); row < gps->gAreaHeight; row++) {
			line = &gps->frameBuffer[row * gps->gAreaWidth];
			
			/**
			 * Calculate the distance from the camera to each screen row.
			 * Rows get further away from the player as they approach the horizon
			 */
			rowDistance = (gps->cHeight / (double)(row - gps->horLine));

			//Calculate row position based upon distance from the right and left
			floorStepX = (rowDistance * (rightRayDirX - leftRayDirX)) / (double)gps->gAreaWidth;
			floorStepY = (rowDistance * (rightRayDirY - leftRayDirY)) / (double)gps->gAreaWidth;

			//Calculate pixel drawing postion for the raycasted row
			floorX = p->pPos.x + rowDistance * leftRayDirX;
			floorY = p->pPos.y + rowDistance * leftRayDirY;

			//Calulcate the floor cast line based upon the cell location relative to the pixel location
			for(x = 0; x < gps->gAreaWidth; x++) {
				//Calculate cell x and y
				gps->cellPos.x = (int)floor(floorX);
				gps->cellPos.y = (int)floor(floorY);

				//Calculate the fractional x and y
				fractionX = floorX - (double)gps->cellPos.x;
				fractionY = floorY - (double)gps->cellPos.y;

				//Calculate the texture coordinates based upon the cell and fractional coordinates
				gps->texPos.x = (int)(fractionX * textureWidth);
				gps->texPos.y = (int)(fractionY * textureHeight);

				//Make sure the texture coordinates are inside the texture
				if(gps->texPos.x < 0) {
					gps->texPos.x = 0;
				}

				else if(gps->texPos.x >= textureWidth) {
					gps->texPos.x = textureWidth - 1;
				}

				if(gps->texPos.y < 0) {
					gps->texPos.y = 0;
				}

				else if(gps->texPos.y >= textureHeight) {
					gps->texPos.y = textureHeight - 1;
				}

				//Build the scanline X position
				line[x] = (tp->floorTexture)->tex[gps->texPos.x * textureHeight + gps->texPos.y];

				//Increment the floor values
				floorX += floorStepX;
				floorY += floorStepY;
			}
		}
	}
}

/**
 * Function to render the ceiling.
 */
void renderCeiling(Screen* s, Game* g, GamePlayScreen* gps) {
	Player* p = g->p;
	TextureProvider* tp = (g->currMap)->texP;

	//Variables needed for floor cells
	gps->cellPos.x = 0;
	gps->cellPos.y = 0;
	gps->texPos.x = 0;
	gps->texPos.y = 0;
	int textureWidth = 0;
	int textureHeight = 0;
	double leftRayDirX = 0.0;
	double leftRayDirY = 0.0;
	double rightRayDirX = 0.0;
	double rightRayDirY = 0.0;

	double rowDistance = 0.0;
	double floorStepX = 0.0;
	double floorStepY = 0.0;
	double floorX = 0.0;
	double floorY = 0.0;
	double fractionX = 0.0;
	double fractionY = 0.0;

	//Frame buffer line
	GrColor* line;

	int row = 0; //Row needed for floor casting
	int x = 0; //X postion needed for floor casting	
	
	//Calculate the floor texture sizes
	textureWidth = (tp->ceilingTexture)->width;
	textureHeight = (tp->ceilingTexture)->height;

	//Calculate the values for the left and right camera edges
	leftRayDirX = gps->rDir.x - gps->pViewPlane.x;
	leftRayDirY = gps->rDir.y - gps->pViewPlane.y;
	rightRayDirX = gps->rDir.x + gps->pViewPlane.x;
	rightRayDirY = gps->rDir.y + gps->pViewPlane.y;

	//Cast and draw the floor below the horizon
	//Make sure we have the floor texture and sizes
	if((gps->frameBuffer != NULL) && (textureWidth > 0) && (textureHeight > 0)) {
		//Loop through the row
		for(row = 0; row <= gps->horLine; row++) {
			line = &gps->frameBuffer[row * gps->gAreaWidth];
			
			/**
			 * Calculate the distance from the camera to each screen row.
			 * Rows get further away from the player as they approach the horizon
			 */
			rowDistance = (gps->cHeight / (double)(row - gps->horLine));

			//Calculate row position based upon distance from the right and left
			floorStepX = (rowDistance * (rightRayDirX - leftRayDirX)) / (double)gps->gAreaWidth;
			floorStepY = (rowDistance * (rightRayDirY - leftRayDirY)) / (double)gps->gAreaWidth;

			//Calculate pixel drawing postion for the raycasted row
			floorX = p->pPos.x + rowDistance * leftRayDirX;
			floorY = p->pPos.y + rowDistance * leftRayDirY;

			//Calulcate the floor cast line based upon the cell location relative to the pixel location
			for(x = 0; x < gps->gAreaWidth; x++) {
				//Calculate cell x and y
				gps->cellPos.x = (int)floor(floorX);
				gps->cellPos.y = (int)floor(floorY);

				//Calculate the fractional x and y
				fractionX = floorX - (double)gps->cellPos.x;
				fractionY = floorY - (double)gps->cellPos.y;

				//Calculate the texture coordinates based upon the cell and fractional coordinates
				gps->texPos.x = (int)(fractionX * textureWidth);
				gps->texPos.y = (int)(fractionY * textureHeight);

				//Make sure the texture coordinates are inside the texture
				if(gps->texPos.x < 0) {
					gps->texPos.x = 0;
				}

				else if(gps->texPos.x >= textureWidth) {
					gps->texPos.x = textureWidth - 1;
				}

				if(gps->texPos.y < 0) {
					gps->texPos.y = 0;
				}

				else if(gps->texPos.y >= textureHeight) {
					gps->texPos.y = textureHeight - 1;
				}

				//Build the scanline X position
				line[x] = (tp->ceilingTexture)->tex[gps->texPos.x * textureHeight + gps->texPos.y];

				//Increment the floor values
				floorX += floorStepX;
				floorY += floorStepY;
			}
		}
	}
}

/**
 * Function to render the entities.
 */
void renderEntities(Screen *s, Game *g, GamePlayScreen* gps) {
	//Get the needed variables, so we don't have to do all of the arrow functions
	Player* p = g->p;
	Map* map = g->currMap;
	TextureProvider* tp = map->texP;
	Entity* currEntity = NULL;

	//Variables for sprite rendering
	double sDistance[MAX_MAP_ENT];
	int sOrder[MAX_MAP_ENT];
	int sCount = 0;
	int sIndex = 0;
	GameTex* entTex = NULL;

	double rDeterminate = 0.0;
	Vec2f relPos;
	Vec2f transPos;
	double spriteStep = 0.0;
	int spritePos = 0;
	int spriteY = 0;
	double texPos = 0.0;
	int spriteHeight = 0;
	int spriteWidth = 0;
	Vec2f startDrawPos;
	Vec2f endDrawPos;
	Vec2f startPos;
	Vec2f endPos;
	int color = 0;
	int j = 0;

	//Calculate sprite distances
	for(int i = 0; i < map->numEntites; i++) {
		currEntity = map->entities[i];

		if((currEntity != NULL) && (currEntity->active)) {
			//Get the distance from the player on both x and y
			relPos.x = (currEntity->ePos).x - p->pPos.x;
			relPos.y = (currEntity->ePos).y - p->pPos.y;
			sOrder[sCount] = i;

			//Calculate the relative distance from the player
			sDistance[i] = (relPos.x * relPos.x) + (relPos.y * relPos.y);
			sCount++;
		}
	}

	//Sort the sprites
	for(int i = 1; i < sCount; i++) {
		sIndex = sOrder[i];
		j = (i - 1);

		while((j >= 0) && sDistance[sOrder[j]] < sDistance[sIndex]) {
			sOrder[(j + 1)] = sOrder[j];
			j--;
		}

		sOrder[(j + 1)] = sIndex;
	}

	//Calculate the render determiniate
	rDeterminate = 1.0f / (gps->pViewPlane.x * gps->rDir.y - gps->rDir.x * gps->pViewPlane.y);

	//Render the entities
	for(int i = 0; i < sCount; i++) {
		currEntity = map->entities[sOrder[i]];
		entTex = tp->entitySprites[currEntity->spriteType];

		if(entTex != NULL) {
			//Get the distance from the player on both x and y
			relPos.x = (currEntity->ePos).x - p->pPos.x;
			relPos.y = (currEntity->ePos).y - p->pPos.y;

			//Calculate transforms
			transPos.x = rDeterminate * (gps->rDir.y * relPos.x - gps->rDir.x * relPos.y);
			transPos.y = rDeterminate * (-gps->pViewPlane.y * relPos.x + gps->pViewPlane.x * relPos.y);

			//Make sure we have a y value
			if(transPos.y > 0.1f) {
				spritePos = (int)(((gps->gAreaWidth - 1) / 2.0f) * (1 + transPos.x / transPos.y));

				spriteHeight = (int)(currEntity->height * gps->gAreaHeight / transPos.y);

				if(spriteHeight > 0) {
					spriteWidth = spriteHeight * entTex->width / entTex->height;

					spriteY = (int)(gps->horLine + gps->gAreaHeight / (2.0 * transPos.y));
					startDrawPos.y = spriteY - spriteHeight;
					endDrawPos.y = spriteY;
					startDrawPos.x = spritePos - spriteWidth / 2;
					endDrawPos.x = startDrawPos.x + spriteWidth;

					//Clip the values if needed
					startPos.x = (startDrawPos.x < 0) ? 0 : startDrawPos.x;
					startPos.y = (startDrawPos.y < 0) ? 0 : startDrawPos.y;
					endPos.x = (endDrawPos.x > gps->gAreaWidth) ? gps->gAreaWidth : endDrawPos.x;
					endPos.y = (endDrawPos.y > gps->gAreaHeight) ? gps->gAreaHeight : endDrawPos.y;

					spriteStep = (double)entTex->height / spriteHeight;

					//Loop through the columns and render
					for(int x = startPos.x; x < endPos.x; x++) {
						if(transPos.y < gps->zBuffer[x]) {
							gps->texPos.x = (x - startDrawPos.x) * entTex->width / spriteWidth;

							if(gps->texPos.x < 0) {
								gps->texPos.x = 0;
							}

							else if(gps->texPos.x > (entTex->width - 1)) {
								gps->texPos.x = (entTex->width - 1);
							}

							texPos = (startPos.y - startDrawPos.y) * spriteStep;

							//Loop through the rows
							for(int y = startPos.y; y < endPos.y; y++) {
								gps->texPos.y = (int)texPos;

								if(gps->texPos.y < 0) {
									gps->texPos.y = 0;
								}

								else if(gps->texPos.y > (entTex->height - 1)) {
									gps->texPos.y = (entTex->height - 1);
								}

								texPos += spriteStep;

								color = entTex->tex[gps->texPos.x * entTex->height + gps->texPos.y];

								if(color != entTex->tColor) {
									gps->frameBuffer[y * gps->gAreaWidth + x] = color;
								}
							}	
						}
					}
				}
			}
		}
	}
}


/**
 * Function to render the walls.
 */
void renderWalls(Screen *s, Game *g, GamePlayScreen* gps) {
	//Get the needed variables, so we don't have to do all of the arrow functions
	Player* p = g->p;
	Map* map = g->currMap;
	TextureProvider* tp = map->texP;

	double cameraX = 0.0;
	double rayDirX = 0.0;
	double rayDirY = 0.0;	
	int mapX = 0;
	int mapY = 0;
	int stepX = 0;
	int stepY = 0;
	double sideDistX = 0.0;
	double sideDistY = 0.0;
	int hit = 0;
	int wallHit = 0;
	int side = 0;
	double distance = 0.0;
	double wallHeight = 0.0;
	int start = 0;
	int end = 0;
	int col = 0;

	GameTex* wallTex = NULL;
	int textureWidth = 0;
	int textureHeight = 0;
	double wallX = 0.0;
	double wallStep = 0.0;
	double texPos = 0.0;
	int y = 0;
	int uncStart = 0;
	MapCell* mc = NULL;
	gps->texPos.x = 0;
	gps->texPos.y = 0;

	//Cast and draw the walls
	for(col = 0; col < gps->gAreaWidth; col++) {
		//Set the z-buffer for this column to the maximum value
		gps->zBuffer[col] = MAX_COL_HEIGHT; 
		hit = 0;
		wallHit = 0;

		cameraX = 2.0 * (double)col / (double)(gps->gAreaWidth - 1) - 1.0;
		rayDirX = (gps->rDir.x) + gps->pViewPlane.x * cameraX;
		rayDirY = (gps->rDir.y) + gps->pViewPlane.y * cameraX;

		mapX = floor(p->pPos.x);
		mapY = floor(p->pPos.y);

		gps->deltaDist.x = (rayDirX == 0.0) ? MAX_COL_HEIGHT : fabs(1.0 / rayDirX);
		gps->deltaDist.y = (rayDirY == 0.0) ? MAX_COL_HEIGHT : fabs(1.0 / rayDirY);

		if(rayDirX < 0) {
			stepX = -1;
			sideDistX = ((p->pPos.x - mapX) * gps->deltaDist.x);
		}

		else {
			stepX = 1;
			sideDistX = ((mapX + 1 - p->pPos.x) * gps->deltaDist.x);
		}

		if(rayDirY < 0) {
			stepY = -1;
			sideDistY = ((p->pPos.y - mapY) * gps->deltaDist.y);
		}
		
		else {
			stepY = 1;
			sideDistY = ((mapY + 1 - p->pPos.y) * gps->deltaDist.y);
		}

		while(hit == 0) {
			if(sideDistX < sideDistY) {
				sideDistX += gps->deltaDist.x;
				mapX += stepX;
				side = 0;
			}

			else {
				sideDistY += gps->deltaDist.y;
				mapY += stepY;
				side = 1;
			}

			mc = getMapCell(map, mapX, mapY);
			
			//No cell here, so consider it a wall
			if(mc == NULL) {
				hit = 1;
			}

			else if((map->mapData[mapY][mapX])->cType != M_CELL_EMPTY) {
				switch((map->mapData[mapY][mapX])->cType) {
					case M_CELL_DOOR:
						hit = 1;
						wallHit = 1;

						//Set the texture
						wallTex = tp->doorTexture;
						textureHeight = wallTex->height;
						textureWidth = wallTex->width;
						break;

					default:
					case M_CELL_WALL:
						hit = 1;
						wallHit = 1;

						//Set the texture
						wallTex = tp->wallTexture;
						textureHeight = wallTex->height;
						textureWidth = wallTex->width;
						break;
				}
			}
		}

		if(wallHit == 0) {
			continue;
		}

		if(side == 0) {
			distance = (rayDirX == 0.0) ? 1e30 : (mapX - p->pPos.x + (1 - stepX) / 2.0) / rayDirX;
			wallX = p->pPos.y + distance * rayDirY;
		}

		else {
			distance = (rayDirY == 0.0) ? 1e30 : (mapY - p->pPos.y + (1 - stepY) / 2.0) / rayDirY;
			wallX = p->pPos.x + distance * rayDirX;
		}

		//Set the distance for the z-buffer for this column
		gps->zBuffer[col] = distance;

		wallHeight = (distance <= 0.0) ? MAX_COL_HEIGHT : (double)gps->gAreaHeight / distance;
		wallX -= floor(wallX);

		//Setup the texture column, flipping the wall when the ray is backwards
		gps->texPos.x = (int)(wallX * textureWidth);

		if(((side == 0) && (rayDirX > 0)) || ((side == 1) && (rayDirY < 0))) {
			gps->texPos.x = textureWidth - gps->texPos.x - 1;
		}

		if(gps->texPos.x < 0) {
			gps->texPos.x = 0;
		}

		if(gps->texPos.x >= textureWidth) {
			gps->texPos.x = textureWidth - 1;
		}

		//Setup unclipped start position so that the wall doesn't look funny
		uncStart = (int)((gps->gAreaHeight / 2.0) - (wallHeight / 2.0));
		wallStep = (double)(textureHeight / wallHeight);

		start = (uncStart < 0) ? 0 : uncStart;
		end = (int)((gps->gAreaHeight / 2.0) + (wallHeight / 2.0));

		if(end >= gps->gAreaHeight) {
			end = gps->gAreaHeight - 1;
		}

		texPos = (start - uncStart) * wallStep;

		//Draw the walls
		for(y = start; y <= end; y++) {
			gps->texPos.y = (int)texPos;

			if(gps->texPos.y >= textureHeight) {
				gps->texPos.y = textureHeight - 1;
			}

			texPos += wallStep;

			gps->frameBuffer[y * gps->gAreaWidth + col] = (wallTex)->tex[gps->texPos.x * textureHeight + gps->texPos.y];
		}
	}
}

/**
 * Function to render the game play area.
 */
void renderGameplayArea(Screen* s, Game* g) {
	//Get the needed variables, so we don't have to do all of the arrow functions
	Player* p = g->p;
	Map* map = g->currMap;
	GamePlayScreen* gps = (GamePlayScreen*)(s->currScreen);

	gps->rDir.x = 0.0;
	gps->rDir.y = 0.0;
	gps->deltaDist.x = 0.0;
	gps->deltaDist.y = 0.0;

	//Calculate player viewing direction and camera plane
	gps->rDir.x = cos(p->angle);
	gps->rDir.y = sin(p->angle);
	gps->pViewPlane.x = -(gps->rDir.y) * tan(p->fov / 2.0);
	gps->pViewPlane.y = gps->rDir.x * tan(p->fov / 2.0);

	//Render the ceiling
	renderCeiling(s, g, gps);

	//Render the floor
	renderFloor(s, g, gps);

	//Render the walls
	renderWalls(s, g, gps);

	//Render the entities
	renderEntities(s, g, gps);

	//Write the framebuffer
	for(int row = 0; row < gps->gAreaHeight; row++) {
		GrPutScanline(0, (gps->gAreaWidth - 1), row, &gps->frameBuffer[row * gps->gAreaWidth], GrWRITE);
	}
}

/**
 * Function to render the hud area.
 */
void renderHudArea(Screen* s, Game* g) {
	//Needed variables
	Player* p = g->p;
	GamePlayScreen* gps = (GamePlayScreen*)(s->currScreen);
	char healthText[20];
	char manaText[20];
	char goldText[20];
	int fullBarWidth = 100;

	//p->currHP = 20;
	p->currMP = 10;

	//Setup the health, mana, and gold text
	sprintf(healthText, "%d/%d", p->currHP, p->maxHP);
	sprintf(manaText, "%d/%d", p->currMP, p->maxMP);
	sprintf(goldText, "Gold: %d", p->gold);

	//Draw the HUD background
    GrBitBlt(s->frame, 0, gps->gAreaHeight, (gps->hudBackground)->image, 0, 0, (gps->hAreaWidth - 1), (gps->hAreaHeight - 1), GrWRITE);

	//Write the player information to the HUD
	renderScreenText(p->name, 4, gps->gAreaHeight + 4, GR_ALIGN_LEFT, GrWhite(), GrNOCOLOR, &GrFont_PC6x8);

	//Full Health
	GrFilledBox(4, gps->gAreaHeight + 13, fullBarWidth, gps->gAreaHeight + 19, GrAllocColor(10, 70, 10));

	//Current Health
	GrFilledBox(4, gps->gAreaHeight + 13, ((fullBarWidth * p->currHP) / p->maxHP), gps->gAreaHeight + 19, GrAllocColor(5, 140, 5));

	//Health text
	renderScreenText(healthText, (fullBarWidth / 2), gps->gAreaHeight + 13, GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC6x8);

	//Full Mana
	GrFilledBox(4, gps->gAreaHeight + 21, fullBarWidth, gps->gAreaHeight + 27, GrAllocColor(10, 10, 70));

	//Current Mana
	GrFilledBox(4, gps->gAreaHeight + 21, ((fullBarWidth * p->currMP) / p->maxMP), gps->gAreaHeight + 27, GrAllocColor(5, 5, 140));

	//Mana text
	renderScreenText(manaText, (fullBarWidth / 2), gps->gAreaHeight + 21, GR_ALIGN_CENTER, GrWhite(), GrNOCOLOR, &GrFont_PC6x8);

	//Gold text
	renderScreenText(goldText, 4, gps->gAreaHeight + 29, GR_ALIGN_LEFT, GrWhite(), GrNOCOLOR, &GrFont_PC6x8);

	//Render the message area
	renderMessageArea(&g->msgA, s, gps);
}
