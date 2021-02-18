#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "map.h"
#include "constants.h"
#include "miner.h"

typedef enum boolean{ false, true } boolean ;

typedef struct Text{
	TTF_Font *font;
	SDL_Texture *fontTexture;
	SDL_Rect rect;
}Text;

struct Game {
	SDL_Window *win;
	SDL_Renderer *renderer;
	SDL_Texture *spriteSheet_T;
	SDL_Texture *miner_spriteSheet;
	Text scoreTxt;
	boolean quit;
	Map GameMap;
	SDL_Rect camera;
	Miner miner;
}*game;

enum { NO_ERROR = 0, ERROR_INIT, ERROR_LOAD_MEDIA };

boolean initGame();
boolean loadMedia();
void destroyGame();
void get_input();
SDL_Texture* loadTexture(char *path);
void updateMiner();
boolean loadFromRenderedText(char *str, SDL_Color textColor);
void renderScore();

#endif
