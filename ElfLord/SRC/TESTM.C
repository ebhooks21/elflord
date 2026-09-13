#include "HEADER/MAPLO.H"
#include "HEADER/MAP.H"
#include "HEADER/GAME.H"
#include <stdio.h>
#include <stdlib.h>

int main() {
	Game* g = malloc(sizeof *g);

	g->currMap = loadMap("START");

	Map* m = g->currMap;

	printf("%d, %d", m->mapRows, m->mapCols);

	for(int i = 0; i < m->mapRows; i++) {
		for(int j = 0; j < m->mapCols; j++) {
			printf("%d", m->mapData[i][j]);
		}

		printf("\n");
	}
}