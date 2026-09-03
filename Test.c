#include <GRX20.H>
#include <GRXKEYS.H>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define MAP_ROWS 6
#define MAP_COLS 10
#define MOVE_STEP 0.15
#define ROT_STEP 0.10

int map[MAP_ROWS][MAP_COLS] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

typedef struct player_t {
	float x;
	float y;
	float angle;
	int moveSpeed;
	int rotSpeed;
	float fov;
} Player;

int isWalkable(float x, float y) {
	int mapX = (int)floor(x);
	int mapY = (int)floor(y);

	if(mapX < 0 || mapX >= MAP_COLS || mapY < 0 || mapY >= MAP_ROWS) {
		return 0;
	}

	return map[mapY][mapX] == 0;
}

void movePlayer(Player* play, double amount) {
	float nextX = play->x + (float)(cos(play->angle) * amount);
	float nextY = play->y + (float)(sin(play->angle) * amount);

	if(isWalkable(nextX, play->y)) {
		play->x = nextX;
	}

	if(isWalkable(play->x, nextY)) {
		play->y = nextY;
	}
}

void rotatePlayer(Player* play, double amount) {
	play->angle += amount;

	if(play->angle < 0.0) {
		play->angle += M_PI * 2.0;
	}
	else if(play->angle >= M_PI * 2.0) {
		play->angle -= M_PI * 2.0;
	}
}

void handleInput(Player* play, int* running) {
	GrKeyType key;

	while(GrKeyPressed() != 0) {
		key = GrKeyRead();

		switch(key) {
			case GrKey_Escape:
				*running = 0;
				break;

			case GrKey_Up:
			case 'w':
			case 'W':
				movePlayer(play, MOVE_STEP);
				break;

			case GrKey_Down:
			case 's':
			case 'S':
				movePlayer(play, -MOVE_STEP);
				break;

			case GrKey_Left:
			case 'a':
			case 'A':
				rotatePlayer(play, -ROT_STEP);
				break;

			case GrKey_Right:
			case 'd':
			case 'D':
				rotatePlayer(play, ROT_STEP);
				break;
		}
	}
}

void render(Player* play) {
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
	static GrContext* frame = NULL;

	int col = 0;

	if(frame == NULL) {
		frame = GrCreateContext(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL);
	}

	if(frame != NULL) {
		GrSetContext(frame);
	}
	else {
		GrSetContext(NULL);
	}

	dirX = cos(play->angle);
	dirY = sin(play->angle);
	planeX = -dirY * tan(play->fov / 2.0);
	planeY = dirX * tan(play->fov / 2.0);

	int groundColor = GrAllocColor(101, 67, 33);

	GrFilledBox(0, 0, SCREEN_WIDTH - 1, (SCREEN_HEIGHT / 2) - 1, skyColor);
	GrFilledBox(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, groundColor);
	//GrClearContext(skyColor);

	for(col = 0; col < SCREEN_WIDTH; col++) {
		hit = 0;
		wallHit = 0;

		cameraX = 2.0 * (double)col / (double)(SCREEN_WIDTH - 1) - 1.0;
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;

		mapX = floor(play->x);
		mapY = floor(play->y);

		deltaDistX = (rayDirX == 0.0) ? 1e30 : fabs(1.0 / rayDirX);
		deltaDistY = (rayDirY == 0.0) ? 1e30 : fabs(1.0 / rayDirY);

		if(rayDirX < 0) {
			stepX = -1;
			sideDistX = ((play->x - mapX) * deltaDistX);
		}

		else {
			stepX = 1;
			sideDistX = ((mapX + 1 - play->x) * deltaDistX);
		}

		if(rayDirY < 0) {
			stepY = -1;
			sideDistY = ((play->y - mapY) * deltaDistY);
		}
		
		else {
			stepY = 1;
			sideDistY = ((mapY + 1 - play->y) * deltaDistY);
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

			if(mapX < 0 || mapX >= MAP_COLS || mapY < 0 || mapY >= MAP_ROWS) {
				hit = 1;
			}
			else if(map[mapY][mapX] > 0) {
				hit = 1;
				wallHit = 1;
			}
		}

		if(wallHit == 0) {
			continue;
		}

		if(side == 0) {
			distance = (rayDirX == 0.0) ? 1e30 : (mapX - play->x + (1 - stepX) / 2.0) / rayDirX;
		}

		else {
			distance = (rayDirY == 0.0) ? 1e30 : (mapY - play->y + (1 - stepY) / 2.0) / rayDirY;
		}

		wallHeight = (distance <= 0.0) ? 1e30 : (double)SCREEN_HEIGHT / distance;

		start = (int)((SCREEN_HEIGHT / 2.0) - (wallHeight / 2.0));
		end = (int)((SCREEN_HEIGHT / 2.0) + (wallHeight / 2.0));

		if(start < 0) {
			start = 0;
		}

		if(end >= SCREEN_HEIGHT) {
			end = SCREEN_HEIGHT - 1;
		}

		//Draw the walls
		GrVLine(col, start, end, wallColor);
	}

	if(frame != NULL) {
		GrSetContext(NULL);
		GrBitBlt(NULL, 0, 0, frame, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, GrWRITE);
	}
}

int main() {
	int running = 1;

    GrSetMode(GR_320_200_graphics);

	Player* play = malloc(sizeof(Player));
	play->x = 3.5;
	play->y = 3.5;
	play->angle = 0;
	play->moveSpeed = 3;
	play->rotSpeed = 2;
	play->fov = M_PI / 3; 

	while(running) {
		handleInput(play, &running);
		render(play);
	}

	GrSetMode(GR_default_text);
	free(play);

	return 0;
}
