#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <unistd.h>

int main(int argc, char *argv[]){
    
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *gWindow;
    bool quit = false;

    gWindow = SDL_CreateWindow("Hellow World!", 1800, 1620, 0);

    SDL_Renderer *gRenderer = SDL_CreateRenderer(gWindow, NULL);

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
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    SDL_Quit();
    return 0;
}
