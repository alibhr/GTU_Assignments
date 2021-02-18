#include <stdio.h>
#include "game.h"

int main(){
	atexit(destroyGame);

	if (!initGame()){ return ERROR_INIT; }
	perror("ERROR1");

	if (!loadMedia()){ return ERROR_LOAD_MEDIA; }
	perror("ERROR2");

	SDL_Color textColor = {0, 0, 0};

	while( !game->quit ){
		get_input();

		SDL_SetRenderDrawColor(game->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(game->renderer);

		updateMiner();

		renderMap(&(game->GameMap), game->renderer, game->spriteSheet_T, &game->miner, &game->camera);
		renderMiner(&(game->miner), game->renderer, game->miner_spriteSheet, &game->camera);
		renderScore(textColor);

		//Update screen
		SDL_RenderPresent(game->renderer);

		//TODO: fps hesaplama
		SDL_Delay(100);
	}

	//destroyGame();

	return NO_ERROR;
}
