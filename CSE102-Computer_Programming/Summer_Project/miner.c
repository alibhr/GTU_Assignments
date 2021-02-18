#include "miner.h"

void setRec(SDL_Rect *r, int x, int y);

void initMiner(Miner *self){
	self->x = 0;
	self->y = 0;
	self->frame = 0;
	self->direction = STANDING;
	self->diamond = 0;
}

void renderMiner(Miner *self, SDL_Renderer *renderer, SDL_Texture *miner_spriteSheet, SDL_Rect *camera){
	SDL_Rect dest = {
		((self->x) + camera->x) * BLOCK_SIZ_DEST,
		((self->y) + camera->y) * BLOCK_SIZ_DEST,
		BLOCK_SIZ_DEST,
		BLOCK_SIZ_DEST
	};

	SDL_Rect src = { 0, 0, BLOCK_SIZ_SRC, BLOCK_SIZ_SRC } ;

	switch (self->direction){
		case STANDING:
			setRec(&src, (self->frame % 6) * BLOCK_SIZ_SRC, 0);
			break;

		case LEFT:
			setRec(&src, (self->frame % 3) * BLOCK_SIZ_SRC, BLOCK_SIZ_SRC);
			break;

		case UP:
			setRec(&src, (self->frame % 4) * BLOCK_SIZ_SRC, BLOCK_SIZ_SRC * 2);
			break;

		case RIGHT:
			setRec(&src, (self->frame % 3) * BLOCK_SIZ_SRC, BLOCK_SIZ_SRC * 3);
			break;

		case DOWN:
			setRec(&src, (self->frame % 4) * BLOCK_SIZ_SRC, BLOCK_SIZ_SRC * 4);
			break;

		case DEAD:
			setRec(&src, (self->frame % 6) * BLOCK_SIZ_SRC, BLOCK_SIZ_SRC * 5);
			break;

		default:
			break;
	}

	SDL_RenderCopy(renderer, miner_spriteSheet, &src, &dest);

	self->frame++;
	if(self->frame>=12) self->frame = 0;
}

void setRec(SDL_Rect *r, int x, int y){
	r->x = x;
	r->y = y;
}
