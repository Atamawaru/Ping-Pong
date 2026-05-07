#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdio.h>
#include <unistd.h>

#define SDL_FLAGS SDL_INIT_VIDEO
struct Game{
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
};


bool game_init_sdl(){
    if (!SDL_Init(SDL_FLAGS)) {
        fprintf(stderr, "Error Initializing SDL3:%s\n", SDL_GetError());
        return false;
    }
    return true;
}

void game_free(SDL_Window** window, SDL_Renderer** renderer){
    // Clean window and renderer, freeing memory and setting pointers to null
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
    *window = NULL;
    *renderer = NULL;
    SDL_Quit();
}


int main(int argc, char *argv[]){
    
    if (!game_init_sdl()){
        return 1;
    }
    struct Game game; 
    SDL_CreateWindowAndRenderer("Hello world!", 1280, 680, 0, &game.gWindow, &game.gRenderer);

    bool quit = false;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type==SDL_EVENT_QUIT) {
                quit=true;
            }
        }
        SDL_SetRenderDrawColorFloat(game.gRenderer, 0, 255, 0, 20);
        SDL_RenderClear(game.gRenderer);
        SDL_RenderPresent(game.gRenderer);
    }
    game_free(&game.gWindow, &game.gRenderer);
    return 0;
}

