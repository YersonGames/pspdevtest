#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspaudio.h>
#include <pspaudiolib.h>
#include <pspuser.h>
#include <string>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;


    SDL_Window* gWindow = nullptr;
    SDL_Renderer* gRender = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) == false) 
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    gWindow = SDL_CreateWindow("window",480,272,0);
    gRender = SDL_CreateRenderer(gWindow,nullptr);

    if (gWindow == nullptr || gRender == nullptr)
    {
        SDL_Quit();
        return 1;
    }

    SDL_FRect square = {216, 96, 34, 64}; 
    bool exitWindow = false;
    SDL_Event event;

    while (exitWindow == false)
    {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                exitWindow = true;
            }
        }
        SDL_RenderClear(gRender);
        SDL_SetRenderDrawColor(gRender,255,255,255,255);
        SDL_RenderFillRect(gRender,&square);
        SDL_RenderPresent(gRender);
    }

    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRender);
    SDL_Quit();
    return 0;
}
