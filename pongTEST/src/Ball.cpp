#include <SDL3/SDL.h>

#include "Ball.h"

Ball::Ball(SDL_FRect get_square)
{
	square = get_square;
}

void Ball::Update()
{
	
}

void Ball::Draw(SDL_Renderer* gRender)
{
	SDL_SetRenderDrawColor(gRender,255,255,255,255);
	SDL_RenderFillRect(gRender,&square);
}