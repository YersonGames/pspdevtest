#include <raylib.h>

#include "Hitbox.h"

Hitbox::Hitbox(float get_x, float get_y, float get_w, float get_h, float get_frameTimer)
{
    x = get_x;
    y = get_y;
    width = get_w;
    height = get_h;
    frameTimer = get_frameTimer;
    destroy = false;
}
void Hitbox::Update()
{
    if (frameTimer > 0)
    {
        frameTimer -= (1.0f*30)*GetFrameTime();
    }
    else
    {
        destroy = true;
    }
}
void Hitbox::Draw()
{
    DrawRectangleLines(x,y,width,height,BLUE);
}

//Getters
float Hitbox::GetX() {return x;}
float Hitbox::GetY() {return y;}
float Hitbox::GetWidth() {return width;}
float Hitbox::GetHeight() {return height;}
bool Hitbox::GetDestroy() {return destroy;}