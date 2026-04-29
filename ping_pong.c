#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdio.h>
#include <unistd.h>

void clean(SDL_Window** window, SDL_Renderer** renderer){
    // Clean window and renderer, freeing memory and setting pointers to null
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
    *window = NULL;
    *renderer = NULL;
}

int main(int argc, char *argv[]){
    
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
    SDL_CreateWindowAndRenderer("Hello world!", 1280, 680, 0, &gWindow, &gRenderer);

    bool quit = false;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type==SDL_EVENT_QUIT) {
                quit=true;
            }
        }
        SDL_SetRenderDrawColorFloat(gRenderer, 0, 255, 0, 20);
        SDL_RenderClear(gRenderer);
        SDL_RenderPresent(gRenderer);
    }
    clean(&gWindow, &gRenderer);
    SDL_Quit();
    return 0;
}

