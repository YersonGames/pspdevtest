#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <memory>

class Player;

class Ball
{
	public:
		SDL_FRect square;
		float hspd;
		float vspd;
		int hmove;
		int vmove;
		
	Ball(SDL_FRect get_square);
	void Update(std::vector<std::unique_ptr<Player>>& players);
	void Draw(SDL_Renderer* gRender);
	
	//Getters
    float GetX();
    float GetY();
    float GetW();
    float GetH();
};