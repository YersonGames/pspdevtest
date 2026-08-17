#pragma once

class Enemy
{
	public:
		float x;
		float y;
		float width;
		float height;
		
	Enemy(float get_x, float get_y, float get_w, float get_h);
	void Update();
	void Draw();
	
	//Getters
    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();
};