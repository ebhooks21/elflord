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
 #include <math.h>

 #define MOVE_STEP 0.15
 #define ROT_STEP 0.10

/**
 * Function to initialize the gameplay screen.
 */
GamePlayScreen* initGPScr(int mRows, int mCols) {
	GamePlayScreen* gps = malloc(sizeof *gps);

	//Initialize the map
	gps->map = initMap(mRows, mCols);

	//Initialize the map data
	(gps->map)->mapData[0][0] = 1;
	(gps->map)->mapData[0][1] = 1;
	(gps->map)->mapData[0][2] = 1;
	(gps->map)->mapData[0][3] = 1;
	(gps->map)->mapData[0][4] = 1;
	(gps->map)->mapData[0][5] = 1;
	(gps->map)->mapData[0][6] = 1;
	(gps->map)->mapData[0][7] = 1;
	(gps->map)->mapData[0][8] = 1;
	(gps->map)->mapData[0][9] = 1;

	(gps->map)->mapData[1][0] = 1;
	(gps->map)->mapData[1][1] = 0;
	(gps->map)->mapData[1][2] = 0;
	(gps->map)->mapData[1][3] = 0;
	(gps->map)->mapData[1][4] = 0;
	(gps->map)->mapData[1][5] = 0;
	(gps->map)->mapData[1][6] = 0;
	(gps->map)->mapData[1][7] = 0;
	(gps->map)->mapData[1][8] = 0;
	(gps->map)->mapData[1][9] = 1;

	(gps->map)->mapData[2][0] = 1;
	(gps->map)->mapData[2][1] = 0;
	(gps->map)->mapData[2][2] = 0;
	(gps->map)->mapData[2][3] = 0;
	(gps->map)->mapData[2][4] = 1;
	(gps->map)->mapData[2][5] = 0;
	(gps->map)->mapData[2][6] = 0;
	(gps->map)->mapData[2][7] = 0;
	(gps->map)->mapData[2][8] = 0;
	(gps->map)->mapData[2][9] = 1;

	(gps->map)->mapData[3][0] = 1;
	(gps->map)->mapData[3][1] = 0;
	(gps->map)->mapData[3][2] = 0;
	(gps->map)->mapData[3][3] = 0;
	(gps->map)->mapData[3][4] = 0;
	(gps->map)->mapData[3][5] = 0;
	(gps->map)->mapData[3][6] = 0;
	(gps->map)->mapData[3][7] = 0;
	(gps->map)->mapData[3][8] = 0;
	(gps->map)->mapData[3][9] = 1;

	(gps->map)->mapData[4][0] = 1;
	(gps->map)->mapData[4][1] = 0;
	(gps->map)->mapData[4][2] = 0;
	(gps->map)->mapData[4][3] = 1;
	(gps->map)->mapData[4][4] = 1;
	(gps->map)->mapData[4][5] = 0;
	(gps->map)->mapData[4][6] = 0;
	(gps->map)->mapData[4][7] = 0;
	(gps->map)->mapData[4][8] = 0;
	(gps->map)->mapData[4][9] = 1;

	(gps->map)->mapData[5][0] = 1;
	(gps->map)->mapData[5][1] = 1;
	(gps->map)->mapData[5][2] = 1;
	(gps->map)->mapData[5][3] = 1;
	(gps->map)->mapData[5][4] = 1;
	(gps->map)->mapData[5][5] = 1;
	(gps->map)->mapData[5][6] = 1;
	(gps->map)->mapData[5][7] = 1;
	(gps->map)->mapData[5][8] = 1;
	(gps->map)->mapData[5][9] = 1;

	return gps;
}

/**
 * Function to render the game play screen.
 */
void renderGameplayScreen(Screen* s, Game* g) {
	//Get the needed variables, so we don't have to do all of the arrow functions
	Player* p = g->p;
	GamePlayScreen* gps = (GamePlayScreen*)(s->currScreen);
	Map* map = gps->map;

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

	dirX = cos(p->angle);
	dirY = sin(p->angle);
	planeX = -dirY * tan(p->fov / 2.0);
	planeY = dirX * tan(p->fov / 2.0);

	int groundColor = GrAllocColor(101, 67, 33);

	GrFilledBox(0, 0, s->width - 1, (s->height / 2) - 1, skyColor);
	GrFilledBox(0, s->height / 2, s->width - 1, s->height - 1, groundColor);

	for(col = 0; col < s->width; col++) {
		hit = 0;
		wallHit = 0;

		cameraX = 2.0 * (double)col / (double)(s->width - 1) - 1.0;
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

		wallHeight = (distance <= 0.0) ? 1e30 : (double)s->height / distance;

		start = (int)((s->height / 2.0) - (wallHeight / 2.0));
		end = (int)((s->height / 2.0) + (wallHeight / 2.0));

		if(start < 0) {
			start = 0;
		}

		if(end >= s->height) {
			end = s->height - 1;
		}

		//Draw the walls
		GrVLine(col, start, end, wallColor);
	}
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

}