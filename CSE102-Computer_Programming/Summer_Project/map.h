#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "constants.h"
#include "miner.h"

enum tile { EMPTY, EARTH, BORDER, ROCK, DIAMOND, L_GATE, O_GATE, MONSTER1, MONSTER2, STAR, MINER};

typedef struct Point2D{
	int x;
	int y;
}Point2D;

typedef struct Map{
	int width;
	int height;
	int tileType;
	enum tile **grid;
	int frame;
	Point2D gate;
}Map;

void renderMap(Map *self, SDL_Renderer *renderer, SDL_Texture *spriteSheet_T, Miner *miner, SDL_Rect *camera);
void initMap(Map *self);
void readTheMap(Map *self, char *fileName, Miner *miner);

#endif
