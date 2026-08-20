#pragma once

#include <SDL3/SDL.h>

class Player
{
    public:
        SDL_FRect square;

    Player(SDL_FRect get_square);
    void Update();
    void Draw(SDL_Renderer* gRender);
};
