#ifndef MINER_H
#define MINER_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "constants.h"

enum Direction { STANDING, RIGHT, LEFT, UP, DOWN, DEAD };

typedef struct Miner{
	int x;
	int y;
	int frame;
	int diamond;
	enum Direction direction;
}Miner;

void initMiner(Miner *self);
void renderMiner(Miner *self, SDL_Renderer *renderer, SDL_Texture *miner_spriteSheet, SDL_Rect *camera);

#endif
