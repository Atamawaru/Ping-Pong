#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define SDL_FLAGS SDL_INIT_VIDEO

#define WINDOW_TITLE "Hello world!"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 640

#define RECT_WIDTH 200
#define RECT_HEIGHT 200

typedef struct game{
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
    SDL_FRect *gRect;
}Game;


bool game_init_sdl(Game *game){
    if (!SDL_Init(SDL_FLAGS)) {
        fprintf(stderr, "Error Initializing SDL3:%s\n", SDL_GetError());
        return false;
    }
    SDL_CreateWindowAndRenderer(
            WINDOW_TITLE, 
            WINDOW_WIDTH, 
            WINDOW_HEIGHT, 
            0, 
            &game->gWindow, &game->gRenderer
    );
    game->gRect=malloc(sizeof(SDL_FRect));
    game->gRect->h=RECT_HEIGHT;
    game->gRect->w=RECT_WIDTH;
    game->gRect->x=(float)WINDOW_WIDTH/2-(float)RECT_WIDTH/2;
    game->gRect->y=(float)WINDOW_HEIGHT/2-(float)RECT_HEIGHT/2;
    
    return true;
}

void game_run(Game *game){
   bool quit = false;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type==SDL_EVENT_QUIT) {
                quit=true;
            }
        }
        SDL_SetRenderDrawColorFloat(game->gRenderer, 0, 255, 0, 20);
        SDL_RenderClear(game->gRenderer);

        SDL_SetRenderDrawColorFloat(game->gRenderer, 255, 0, 0, 255);
        SDL_RenderFillRect(game->gRenderer, game->gRect);
        SDL_RenderPresent(game->gRenderer);
    }
 
}

void game_free(Game *game){
    // Clean window and renderer, freeing memory and setting pointers to null
    SDL_DestroyRenderer(game->gRenderer);
    SDL_DestroyWindow(game->gWindow);
    game->gWindow = NULL;
    game->gRenderer = NULL;
    free(game->gRect);
    SDL_Quit();
}


int main(int argc, char *argv[]){
    bool exit_status=EXIT_FAILURE;
    Game game = {0};
    if (game_init_sdl(&game)){
        exit_status=EXIT_SUCCESS;
    } 
    game_run(&game); 
    game_free(&game);
    return exit_status;
}

