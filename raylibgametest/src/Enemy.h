#pragma once
#include <raylib.h>

class Enemy
{
	public:
		float x;
		float y;
		float width;
		float height;
		Rectangle hurtbox;
		
		
	Enemy(float get_x, float get_y, float get_w, float get_h, Rectangle get_hurtbox);
	void Update();
	void Draw();
	
	//Getters
    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();
};