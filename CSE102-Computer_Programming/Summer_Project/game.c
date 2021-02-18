#include "game.h"

void handleKeyDown(SDL_Event e);
void handleKeyUp(SDL_Event e);
void go(Point2D dest);

boolean initGame(){
	game = (struct Game*)malloc(sizeof(struct Game));
	game->win = NULL;
	game->quit = false;
	game->renderer = NULL;
	game->spriteSheet_T = NULL;
	initMiner( &game->miner );
	initMap(&game->GameMap);
	readTheMap(&game->GameMap, "level/L0.txt", &game->miner);
	game->miner_spriteSheet = NULL;
	game->camera.x = 0;
	game->camera.y = 0;
	game->camera.w = CAMERA_WIDTH;
	game->camera.h = CAMERA_HEIGHT;
	game->scoreTxt.font = NULL;
	game->scoreTxt.fontTexture = NULL;
	game->scoreTxt.rect.x = 0;
	game->scoreTxt.rect.y = 0;

	if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}

	game->win = SDL_CreateWindow(
		TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if(game->win == NULL){
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}

	game->renderer = SDL_CreateRenderer(game->win, -1, SDL_RENDERER_ACCELERATED);
	if(game->renderer == NULL){
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(game->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)){
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	if(TTF_Init() == -1){
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}

	return true;
}

boolean loadMedia(){

	if( (game->spriteSheet_T = loadTexture("res/tileset.png")) == NULL ) { return false; }
	if( (game->miner_spriteSheet = loadTexture("res/miner.png")) == NULL ) { return false; }

	game->scoreTxt.font = TTF_OpenFont("res/text.ttf",32);
	if(game->scoreTxt.font == NULL){
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

boolean loadFromRenderedText(char *str, SDL_Color textColor){

	if(game->scoreTxt.fontTexture != NULL){
		SDL_DestroyTexture(game->scoreTxt.fontTexture);
		game->scoreTxt.fontTexture = NULL;
	}

	SDL_Surface *textSurface = TTF_RenderText_Solid(game->scoreTxt.font, str, textColor);
	if(textSurface == NULL ){
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	game->scoreTxt.fontTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);

	if(game->scoreTxt.fontTexture == NULL){
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	game->scoreTxt.rect.w = textSurface->w;
	game->scoreTxt.rect.h = textSurface->h;

	SDL_FreeSurface(textSurface);

	return true;
}

void destroyGame(){
	SDL_DestroyTexture(game->spriteSheet_T);
	game->spriteSheet_T = NULL;

	TTF_CloseFont(game->scoreTxt.font);

	//SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->win);
	game->win = NULL;
	game->renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

void get_input(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type){
		case SDL_QUIT:
			game->quit = true;
			break;
		
		case SDL_KEYDOWN:
			handleKeyDown(event);
			break;

		case SDL_KEYUP:
			handleKeyUp(event);
			break;
		}
	}
}

SDL_Texture* loadTexture(char *path){
	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurface = IMG_Load(path);
	if(loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
		exit(ERROR_LOAD_MEDIA);
	}

	newTexture = SDL_CreateTextureFromSurface(game->renderer, loadedSurface);

	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

void handleKeyDown(SDL_Event e){
	switch (e.key.keysym.sym){
		case SDLK_UP: game->miner.direction = UP ; break;
		case SDLK_DOWN: game->miner.direction = DOWN ; break;
		case SDLK_LEFT: game->miner.direction = LEFT ; break;
		case SDLK_RIGHT: game->miner.direction = RIGHT ; break;
	}
}

void handleKeyUp(SDL_Event e){
	switch (e.key.keysym.sym){
		case SDLK_UP:
			if(game->miner.direction == UP) game->miner.direction = STANDING;
			break;
		case SDLK_DOWN:
			if(game->miner.direction == DOWN) game->miner.direction = STANDING;
			break;
		case SDLK_LEFT:
			if(game->miner.direction == LEFT) game->miner.direction = STANDING;
			break;
		case SDLK_RIGHT:
			if(game->miner.direction == RIGHT) game->miner.direction = STANDING;
			break;
	}
}

void updateMiner(){

	Point2D dest = { game->miner.x, game->miner.y };
	game->GameMap.grid[game->miner.y][game->miner.x] = EMPTY;

	switch(game->miner.direction){
		case UP:
			--(dest.y);
			break;
		case DOWN:
			++(dest.y);
			break;
		case RIGHT:
			++(dest.x);
			break;
		case LEFT:
			--(dest.x);
			break;
		default: break;
	}

	switch (game->GameMap.grid[dest.y][dest.x]){
		case EMPTY:
			go(dest);
			break;
		case EARTH:
			go(dest);
			break;
		case BORDER:
			break;
		case ROCK:
			break;
		case DIAMOND:
			go(dest);
			++game->miner.diamond;
			break;
		case L_GATE:
			break;
		case O_GATE:
			break;
		case MONSTER1:
			break;
		case MONSTER2:
			break;
		case STAR:
			break;
		default : break;
	}

	game->GameMap.grid[game->miner.y][game->miner.x] = MINER;
}

void go(Point2D dest){
	game->miner.y = dest.y;
	game->miner.x = dest.x;
}

void renderScore(SDL_Color textColor){
	char *s = NULL;
	int diamond = game->miner.diamond;

	int i=0;

	while(diamond>0){
		++i;
		diamond /=10;
	}diamond = game->miner.diamond;

	if(diamond==0) ++i;

	s = (char*)malloc(sizeof(char) * (i+1) );

	s[i] = '\0';
	for(; i>0 ; i--){
		s[i-1] = '0' + (diamond % 10);
		diamond /=10; 
	}

	loadFromRenderedText(s,textColor);
	SDL_RenderCopy(game->renderer, game->scoreTxt.fontTexture, NULL, &game->scoreTxt.rect);
	free(s);
}
