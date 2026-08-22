#include <SDL3/SDL.h>

#include "Player.h"
#include "Ball.h"

Player::Player(SDL_FRect get_square)
{
    square = get_square;
	spd = 5.0f;
}

void Player::Update(SceCtrlData& pad, Ball& ball)
{
	if (pad.Buttons & PSP_CTRL_UP)
	{
		square.y -= spd;
	}
	else if (pad.Buttons & PSP_CTRL_DOWN)
	{
		square.y += spd;
	}
	
	if (square.y < 0) {square.y = 0;}
	else if (square.y+square.h > 272) {square.y = 272-square.h;}
}
void Player::Draw(SDL_Renderer* gRender)
{
    SDL_SetRenderDrawColor(gRender,255,255,255,255);
    SDL_RenderFillRect(gRender,&square);
}

//Getters
float Player::GetX() {return square.x;}
float Player::GetY() {return square.y;}
float Player::GetW() {return square.w;}
float Player::GetH() {return square.h;}

//Enemy

Enemy::Enemy(SDL_FRect get_square)  : Player(get_square)
{
	square = get_square;
}

void Enemy::Update(SceCtrlData& pad, Ball& ball)
{
	if (square.y+(square.h/2) > ball.GetY()+ball.GetH())
	{
		square.y -= 4;
	}
	else if (square.y+(square.h/2) < ball.GetY())
	{
		square.y += 4;
	}
	
	if (square.y <= 0) {square.y = 0;}
	else if (square.y+square.h >= 272) {square.y = 272-square.h;}
}

void Enemy::Draw(SDL_Renderer* gRender)
{
	SDL_SetRenderDrawColor(gRender,255,255,255,255);
    SDL_RenderFillRect(gRender,&square);
}
