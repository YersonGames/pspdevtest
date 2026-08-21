#pragma once

#include <SDL3/SDL.h>

class Ball
{
	public:
		SDL_FRect square;
		
	Ball(SDL_FRect get_square);
	void Update();
	void Draw(SDL_Renderer* gRender);
};