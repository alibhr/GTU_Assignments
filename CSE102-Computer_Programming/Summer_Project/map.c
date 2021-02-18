#include "map.h"

void putTile(enum tile *m ,char c);
void renderTile(enum tile m, int i, int j, int frame, SDL_Renderer *renderer, SDL_Texture *spriteSheet_T, int tileType);
void setRect(SDL_Rect *r, int x, int y);
void update_camera(Miner *miner, SDL_Rect *camera, int map_width, int map_height);

void initMap(Map *self){
	self->width = -1;
	self->height = -1;
	self->grid = NULL;
	self->frame = 0;
	self->tileType = 0;
	self->gate.x = 0;
	self->gate.y = 0;
}

void readTheMap(Map *self, char *fileName, Miner *miner){
	FILE *filep = fopen(fileName,"r");
	char temp[BUFF_SIZ16];
	char c;
	int minerCounter = 0;

	fscanf(filep,"%s",temp);
	fscanf(filep,"%d",&self->tileType);

	fscanf(filep,"%s",temp);
	fscanf(filep,"%d",&self->width);

	fscanf(filep,"%s",temp);
	fscanf(filep,"%d",&self->height);

	self->grid = (enum tile**)malloc(sizeof(enum tile*) * self->height);
	for(int i=0 ; i<self->height ; ++i){
		self->grid[i] = (enum tile*)malloc(sizeof(enum tile) * self->width);
	}

	fgetc(filep);
	for(int i=0 ; i<self->height; ++i){
		for(int j=0 ; j<self->width ; ++j){
			c = fgetc(filep);
			if(c == 'm'){
				miner->x = j;
				miner->y = i;
				miner->direction = STANDING;
				++minerCounter;
			}
			else if(c == 'l' || c == 'o'){
				self->gate.x = j;
				self->gate.y = i;
			}
			putTile(&(self->grid[i][j]),c);
		}
		fgetc(filep);
	}

	if(minerCounter < 1){
		printf("ERROR : There is no miner in this file !!\n");
		exit(1);
	}
	else if(minerCounter > 1){
		perror("ERROR : There are more than 1 miner in this file !!\n");	
		exit(1);
	}

	fclose(filep);
}

void putTile(enum tile *m ,char c){
	switch (c){
		case 'b': *m = BORDER;	break;
		case 'r': *m = ROCK;	break;
		case 'e': *m = EARTH;	break;
		case ' ': *m = EMPTY;	break;
		case 'd': *m = DIAMOND;	break;
		case 'm': *m = MINER;	break;
		case 'x': *m = MONSTER1;break;
		case 'X': *m = MONSTER2;break;
		case 's': *m = STAR;	break;
		case 'l': *m = L_GATE;	break;
		case 'o': *m = O_GATE;	break;
		default : *m = EMPTY;	break;
	}
}

void renderMap(Map *self, SDL_Renderer *renderer, SDL_Texture *spriteSheet_T, Miner *miner, SDL_Rect *camera){

	update_camera(miner, camera, self->width, self->height);

	for(int i=0 ; i<self->height ; ++i){
		for(int j=0 ; j<self->width ; ++j){
			renderTile(self->grid[i][j], j + camera->x, i + camera->y, self->frame, renderer, spriteSheet_T, self->tileType);
		}
	}
	self->frame++;
	if(self->frame>=4) self->frame = 0;
}

void renderTile(enum tile m, int i, int j, int frame, SDL_Renderer *renderer, SDL_Texture *spriteSheet_T, int tileType){

	SDL_Rect src = { 0, 0, BLOCK_SIZ_SRC, BLOCK_SIZ_SRC };
	SDL_Rect dest = { i*BLOCK_SIZ_DEST, j*BLOCK_SIZ_DEST, BLOCK_SIZ_DEST, BLOCK_SIZ_DEST };

	switch (m){
		case EMPTY:
			setRect(&src, 2*BLOCK_SIZ_SRC, tileType*BLOCK_SIZ_SRC*4);
			break;
		
		case EARTH:
			setRect(&src, 1*BLOCK_SIZ_SRC, tileType*BLOCK_SIZ_SRC*4);
			break;

		case BORDER:
			setRect(&src, 0, tileType*BLOCK_SIZ_SRC*4);
			break;

		case ROCK:
			setRect(&src, 3*BLOCK_SIZ_SRC, frame*BLOCK_SIZ_SRC + tileType*BLOCK_SIZ_SRC*4);
			break;

		case DIAMOND:
			setRect(&src, 4*BLOCK_SIZ_SRC, frame*BLOCK_SIZ_SRC+tileType*BLOCK_SIZ_SRC*4);
			break;

		case L_GATE:
			setRect(&src, 8*BLOCK_SIZ_SRC, frame*BLOCK_SIZ_SRC+tileType*BLOCK_SIZ_SRC*4);
			break;

		case O_GATE:
			setRect(&src, 6*BLOCK_SIZ_SRC, frame*BLOCK_SIZ_SRC+tileType*BLOCK_SIZ_SRC*4);
			break;

		case MONSTER1:
			setRect(&src, 9*BLOCK_SIZ_SRC, frame*BLOCK_SIZ_SRC+tileType*BLOCK_SIZ_SRC*4);
			break;

		case MONSTER2:
			setRect(&src, 10*BLOCK_SIZ_SRC, frame*BLOCK_SIZ_SRC+tileType*BLOCK_SIZ_SRC*4);
			break;

		case STAR:
			setRect(&src, 11*BLOCK_SIZ_SRC, frame*BLOCK_SIZ_SRC+tileType*BLOCK_SIZ_SRC*4);
			break;

		case MINER:
			return;
			break;
		
		default:
			return;
			break;
	}
	SDL_RenderCopy(renderer, spriteSheet_T, &src, &dest);
}

void setRect(SDL_Rect *r, int x, int y){
	r->x = x;
	r->y = y;
}

void update_camera(Miner *miner, SDL_Rect *camera, int map_width, int map_height){
	if( (camera->w / BLOCK_SIZ_DEST) - camera->x < miner->x + (SCREEN_WIDTH/BLOCK_SIZ_DEST)/5){
		camera->x -= 1;
	}

	if( (camera->w / BLOCK_SIZ_DEST) - camera->x > miner->x + (SCREEN_WIDTH/BLOCK_SIZ_DEST)/5*4){
		camera->x += 1;
	}

	if( (camera->h / BLOCK_SIZ_DEST) - camera->y < miner->y + (CAMERA_HEIGHT/BLOCK_SIZ_DEST)/5){
		camera->y -= 1;
	}

	if( (camera->h / BLOCK_SIZ_DEST) - camera->y > miner->y + (CAMERA_HEIGHT/BLOCK_SIZ_DEST)/5*4){
		camera->y += 1;
	}

	if(camera->x > 0)
		camera->x = 0;
	if(camera->y > 0)
		camera->y = 0;
	if((-1*camera->x) > map_width-(camera->w/BLOCK_SIZ_DEST) )
		camera->x = -1*(map_width-(camera->w/BLOCK_SIZ_DEST));

	if((-1*camera->y) > map_height-(camera->h/BLOCK_SIZ_DEST) )
		camera->y = -1*(map_height-(camera->h/BLOCK_SIZ_DEST));
}
	