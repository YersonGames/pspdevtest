#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>

#include "Ball.h"
#include "gameutils.h"

Ball::Ball(SDL_FRect get_square)
{
	square = get_square;
	hspd = 2;
	vspd = 0.05;
	hmove = -1;
	vmove = -1+SDL_rand(3);
	if (vmove == 0) {vmove = -1;}
}

void Ball::Update(std::vector<std::unique_ptr<Player>>& players)
{
	square.x+=(hspd*hmove);
	square.y+=((float)vspd*vmove);
	
	for (auto player = players.begin(); player != players.end(); player++)
	{
		if (gameutils::getCollisionPtr(square.x+(hspd*hmove),square.y,square.w,square.h,player->get()))
		{
			if (hmove == 1) {hmove = -1;}
			else if (hmove == -1) {hmove = 1;}
			
			hspd += 1;
			vspd += 0.05;
		}
	}
	
	if (square.y-vspd <= 0) {vmove = 1;}
	else if (square.y+vspd >= 272) {vmove = -1;}
	
	if (hspd > 12) {hspd = 12;}
}

void Ball::Draw(SDL_Renderer* gRender)
{
	SDL_SetRenderDrawColor(gRender,255,255,255,255);
	SDL_RenderFillRect(gRender,&square);
}

//Getters
float Ball::GetX() {return square.x;}
float Ball::GetY() {return square.y;}
float Ball::GetW() {return square.w;}
float Ball::GetH() {return square.h;}