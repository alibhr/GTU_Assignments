#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 100
#define FPS 60
#define BLOCK_PX 32
#define STAND 7/*total frame number when the character standing*/
#define THINK 7;
enum {
	dead,
    standing,
    standing1,
    standing2,
    move_to_left,
    move_to_right,
    max
};
struct game{
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Texture *sprite_sheet;
}game;

struct animation{
    int total_frame;
    int th_frame;
    int think_time;
    SDL_Rect source;
    SDL_Rect dest;
};
struct animation standing_player;

void draw();
void clean();
void get_input();
void init_animation(struct animation *something,int x,int y,int total_frame);
void go_next_frame(struct animation *something,int y);

int main(){
    atexit(clean);
    if(SDL_Init(SDL_INIT_VIDEO)){
        printf("ERROR init:%s\n",SDL_GetError());
		SDL_Quit();
    }
    game.win=SDL_CreateWindow("  ",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								SCREEN_WIDTH,SCREEN_HEIGHT,0);
	if(!game.win){
		printf("ERROR SDL_CreateWindow:%s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

    game.rend=SDL_CreateRenderer(game.win,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(!game.rend){
		printf("ERROR SDL_CreateRenderer:%s\n",SDL_GetError());
		SDL_DestroyWindow(game.win);
		SDL_Quit();
		exit(1);
	}

    game.sprite_sheet=IMG_LoadTexture(game.rend,"sprites.png");
    if(!game.sprite_sheet){
        printf("ERROR sprite sheet loading\n");
		SDL_DestroyWindow(game.win);
		SDL_Quit();
		exit(1);
    }

    init_animation(&standing_player,0,0,STAND);  
    

    while(1){
        get_input();
        draw();
        SDL_RenderPresent(game.rend);
        SDL_Delay(1000/FPS);
    }
    return 0;
}
void get_input(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type){
        case SDL_QUIT:
            exit(1);
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode){
            case SDL_SCANCODE_ESCAPE:
                exit(1);
                break;
            }
            break;
        }
    }
}
void draw(){

    SDL_SetRenderDrawColor(game.rend,0,0,0,255);
	SDL_RenderFillRect(game.rend, NULL);
	SDL_RenderClear(game.rend);

    go_next_frame(&standing_player,standing);

    SDL_RenderCopy(game.rend,game.sprite_sheet,&standing_player.source,&standing_player.dest);
}
void clean(){
    SDL_DestroyTexture(game.sprite_sheet);
    SDL_DestroyWindow(game.win);
    SDL_DestroyRenderer(game.rend);
    SDL_Quit();
    printf("DONE\n");
}
void init_animation(struct animation *something,int x,int y,int total_frame){
    memset(&standing_player,0,sizeof(struct animation));
    something->th_frame=0;
    something->total_frame=total_frame;
    something->dest.x=x;
    something->dest.y=y;
    something->dest.w=BLOCK_PX*3;
    something->dest.h=BLOCK_PX*3;
    something->source.w=BLOCK_PX;
    something->source.h=BLOCK_PX;
}
void go_next_frame(struct animation *something,int y){
    if(something->think_time <=0){
        something->th_frame=(standing_player.th_frame+1)%8;
        something->source.x=(standing_player.th_frame*BLOCK_PX)%(BLOCK_PX*STAND);
        something->source.y=y*BLOCK_PX;
        something->think_time=THINK;
    }
    else{
        something->think_time--;
    }
}
