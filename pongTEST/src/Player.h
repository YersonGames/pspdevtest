#pragma once

#include <SDL3/SDL.h>
#include <pspctrl.h>

class Ball;

class Player
{
    public:
        SDL_FRect square;
		float spd;

    Player(SDL_FRect get_square);
    virtual void Update(SceCtrlData& pad, Ball& ball);
    virtual void Draw(SDL_Renderer* gRender);

    //Getters
    float GetX();
    float GetY();
    float GetW();
    float GetH();
};


class Enemy : public Player
{
	public:
		Enemy(SDL_FRect get_square);
		void Update(SceCtrlData& pad, Ball& ball) override;
		void Draw(SDL_Renderer* gRender) override;
};
