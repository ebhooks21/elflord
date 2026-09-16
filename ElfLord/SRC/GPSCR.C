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
 #include <GRX20.H>
 #include <stdlib.h>
 #include <stdio.h>
 #include <math.h>

/**
 * Function to initialize the gameplay screen.
 */
GamePlayScreen* initGPScr(Screen* s) {
	GamePlayScreen* gps = malloc(sizeof *gps);

	gps->hAreaWidth = s->width;
	gps->hAreaHeight = 40; 
	gps->gAreaWidth = s->width - 1;
	gps->gAreaHeight = (s->height - gps->hAreaHeight);

	//Load the hud background
	gps->hudBackground = GrCreateContext(gps->hAreaWidth, gps->hAreaHeight, NULL, NULL);
    GrLoadContextFromPnm(gps->hudBackground, "ASSET\\hud.ppm");

	//Load the ceiling texture 
	gps->floorTexture = GrCreateContext(gps->gAreaWidth, (gps->gAreaHeight / 2), NULL, NULL);
    GrLoadContextFromPnm(gps->floorTexture, "ASSET\\stonef.ppm");

	//Create the floor scanline
	//This needs to store a color for each ray of the floor from X0 to X1
	gps->floorScanline = malloc(sizeof(GrColor) * gps->gAreaWidth);

	return gps;
}

/**
 * Function to destroy the gameplay screen.
 */
void destoryGPScr(GamePlayScreen* g) {
	//Destroy the textures
	if(g->hudBackground != NULL) {
		GrDestroyContext(g->hudBackground);
	} 

	if(g->floorTexture != NULL) {
		GrDestroyContext(g->floorTexture);
	}

	//Free the contexts and scanline
	free(g->ceilingTexture);
	free(g->floorScanline);
	free(g->floorTexture);
	free(g->hudBackground);

	//Destroy the gameplay screen
	free(g);
}

/**
 * Function to render the game play screen.
 */
void renderGameplayScreen(Screen* s, Game* g) {
	//Get the needed variables, so we don't have to do all of the arrow functions
	Player* p = g->p;
	Map* map = g->currMap;
	GamePlayScreen* gps = (GamePlayScreen*)(s->currScreen);

	double dirX = 0.0;
	double dirY = 0.0;
	double planeX = 0.0;
	double planeY = 0.0;
	double cameraX = 0.0;
	double rayDirX = 0.0;
	double rayDirY = 0.0;	
	int mapX = 0;
	int mapY = 0;
	double deltaDistX = 0.0;
	double deltaDistY = 0.0;
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
	int skyColor = GrAllocColor(0, 0, 135);
	int wallColor = GrAllocColor(200, 200, 200);
	int col = 0;

	//Values floor casting
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

	//Variables needed for floor cells
	int cellX = 0;
	int cellY = 0;
	int textureX = 0;
	int textureY = 0;
	int textureWidth = 0;
	int textureHeight = 0;

	//Calculate horizon start line
	int horizon = gps->gAreaHeight / 2; //Horizon line is half the screen

	int row = 0; //Row needed for floor casting
	int x = 0; //X postion needed for floor casting	

	/**
	 * This is calculated based upon the idea that the player's viewpoint
	 * is roughly halfway up a single wall instance, which is equal to
	 * the view area height.
	 */
	double cameraHeight = (0.5 * (double)gps->gAreaHeight);

	//Calculate the floor texture sizes
	textureWidth = ((gps->floorTexture)->gc_xmax + 1);
	textureHeight = ((gps->floorTexture)->gc_ymax + 1);
	
	//Calculate player viewing direction and camera plane
	dirX = cos(p->angle);
	dirY = sin(p->angle);
	planeX = -dirY * tan(p->fov / 2.0);
	planeY = dirX * tan(p->fov / 2.0);

	//Draw the sky, with it going slightly past the horizon line
	GrFilledBox(0, 0, (gps->gAreaWidth - 1), horizon, skyColor);
    //GrBitBlt(s->frame, 0, (gps->gAreaHeight / 2), gps->floorTexture, 0, 0, (gps->gAreaWidth - 1), (gps->gAreaHeight - 1), GrWRITE);

	//Calculate the values for the left and right camera edges
	leftRayDirX = dirX - planeX;
	leftRayDirY = dirY - planeY;
	rightRayDirX = dirX + planeX;
	rightRayDirY = dirY + planeY;

	//Cast and draw the floor below the horizon
	//Make sure we have the floor texture and sizes
	if((gps->floorScanline != NULL) && (textureWidth > 0) && (textureHeight > 0)) {
		//Loop through the row
		for(row = (horizon + 1); row < gps->gAreaHeight; row++) {
			/**
			 * Calculate the distance from the camera to each screen row.
			 * Rows get further away from the player as they approach the horizon
			 */
			rowDistance = (cameraHeight / (double)(row - horizon));

			//Calculate row position based upon distance from the right and left
			floorStepX = (rowDistance * (rightRayDirX - leftRayDirX)) / (double)gps->gAreaWidth;
			floorStepY = (rowDistance * (rightRayDirY - leftRayDirY)) / (double)gps->gAreaWidth;

			//Calculate pixel drawing postion for the raycasted row
			floorX = (p->xLoc + rowDistance) * leftRayDirX;
			floorY = (p->yLoc + rowDistance) * leftRayDirY;

			//Calulcate the floor cast line based upon the cell location relative to the pixel location
			for(x = 0; x < gps->gAreaWidth; x++) {
				//Calculate cell x and y
				cellX = (int)floor(floorX);
				cellY = (int)floor(floorY);

				//Calculate the fractional x and y
				fractionX = floorX - (double)cellX;
				fractionY = floorY - (double)cellY;

				//Calculate the texture coordinates based upon the cell and fractional coordinates
				textureX = (int)(fractionX * textureWidth);
				textureY = (int)(fractionY * textureHeight);

				//Make sure the texture coordinates are inside the texture
				if(textureX < 0) {
					textureX = 0;
				}

				else if(textureX >= textureWidth) {
					textureX = textureWidth - 1;
				}

				if(textureY < 0) {
					textureY = 0;
				}

				else if(textureY >= textureHeight) {
					textureY = textureHeight - 1;
				}

				//Build the scanline X position
				gps->floorScanline[x] = GrPixelC(gps->floorTexture, textureX, textureY);

				//Increment the floor values
				floorX += floorStepX;
				floorY += floorStepY;
			}

			//Place the calculated scanline on the context
			GrPutScanline(0, gps->gAreaWidth - 1, row, gps->floorScanline, GrWRITE);
		}
	}

	//Cast and draw the walls
	for(col = 0; col < gps->gAreaWidth; col++) {
		hit = 0;
		wallHit = 0;

		cameraX = 2.0 * (double)col / (double)(gps->gAreaWidth - 1) - 1.0;
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;

		mapX = floor(p->xLoc);
		mapY = floor(p->yLoc);

		deltaDistX = (rayDirX == 0.0) ? 1e30 : fabs(1.0 / rayDirX);
		deltaDistY = (rayDirY == 0.0) ? 1e30 : fabs(1.0 / rayDirY);

		if(rayDirX < 0) {
			stepX = -1;
			sideDistX = ((p->xLoc - mapX) * deltaDistX);
		}

		else {
			stepX = 1;
			sideDistX = ((mapX + 1 - p->xLoc) * deltaDistX);
		}

		if(rayDirY < 0) {
			stepY = -1;
			sideDistY = ((p->yLoc - mapY) * deltaDistY);
		}
		
		else {
			stepY = 1;
			sideDistY = ((mapY + 1 - p->yLoc) * deltaDistY);
		}

		while(hit == 0) {
			if(sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}

			else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			if(mapX < 0 || mapX >= map->mapCols || mapY < 0 || mapY >= map->mapRows) {
				hit = 1;
			}
			else if(map->mapData[mapY][mapX] > 0) {
				hit = 1;
				wallHit = 1;
			}
		}

		if(wallHit == 0) {
			continue;
		}

		if(side == 0) {
			distance = (rayDirX == 0.0) ? 1e30 : (mapX - p->xLoc + (1 - stepX) / 2.0) / rayDirX;
		}

		else {
			distance = (rayDirY == 0.0) ? 1e30 : (mapY - p->yLoc + (1 - stepY) / 2.0) / rayDirY;
		}

		wallHeight = (distance <= 0.0) ? 1e30 : (double)gps->gAreaHeight / distance;

		start = (int)((gps->gAreaHeight / 2.0) - (wallHeight / 2.0));
		end = (int)((gps->gAreaHeight / 2.0) + (wallHeight / 2.0));

		if(start < 0) {
			start = 0;
		}

		if(end >= gps->gAreaHeight) {
			end = gps->gAreaHeight - 1;
		}

		//Draw the walls
		GrVLine(col, start, end, wallColor);
	}

	//Draw the hud area
	renderHudArea(s, g);
}

/**
 * Function to render the game play area.
 */
void renderGameplayArea(Screen* s, Game* g) {

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

	//Setup the health, mana, and gold text
	sprintf(healthText, "HP: %d/%d", p->currHP, p->maxHP);
	sprintf(manaText, "MP: %d/%d", p->currMP, p->maxMP);
	sprintf(goldText, "Gold: %d", p->gold);

	//Draw the HUD background
    GrBitBlt(s->frame, 0, gps->gAreaHeight, gps->hudBackground, 0, 0, (gps->hAreaWidth - 1), (gps->hAreaHeight - 1), GrWRITE);

	//Write the player information to the HUD
	renderScreenText(p->name, 4, gps->gAreaHeight + 4, GR_ALIGN_LEFT, GrWhite(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText(healthText, 4, gps->gAreaHeight + 13, GR_ALIGN_LEFT, GrWhite(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText(manaText, 4, gps->gAreaHeight + 21, GR_ALIGN_LEFT, GrWhite(), GrNOCOLOR, &GrFont_PC6x8);
	renderScreenText(goldText, 4, gps->gAreaHeight + 29, GR_ALIGN_LEFT, GrWhite(), GrNOCOLOR, &GrFont_PC6x8);
}