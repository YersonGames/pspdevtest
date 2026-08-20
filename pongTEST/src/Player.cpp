#include <SDL3/SDL.h>

#include "Player.h"

Player::Player(SDL_FRect get_square)
{
    square = get_square;
}

void Player::Update()
{

}
void Player::Draw(SDL_Renderer* gRender)
{
    SDL_SetRenderDrawColor(gRender,255,255,255,255);
    SDL_RenderFillRect(gRender,&square);
}
