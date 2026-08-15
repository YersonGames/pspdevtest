#include <raylib.h>

#include "Hurtbox.h"
#include "utils.h"
#include "Hitbox.h"

Hurtbox::Hurtbox(float get_x, float get_y, float get_w, float get_h)
{
    x = get_x;
    y = get_y;
    width = get_w;
    height = get_h;
    hurtTimer = 0.0f;
    hurtColor = {0,255,0,255};

    hurt = false;
}
void Hurtbox::Update(std::vector<Hitbox>& hitboxes)
{

    if (hurt == true)
    {
        if (hurtTimer > 0)
        {
            hurtTimer -= (1.0f*30)*GetFrameTime();
            hurtColor = {255,0,0,255};
        }
        else
        {
            hurtColor = {0,255,0,255};
            hurt = false;
        }
    }

    for (auto hitbox = hitboxes.begin(); hitbox != hitboxes.end(); hitbox++)
    {
        if (utils::getCollision(x,y,width,height,*hitbox) && hurt == false)
        {
            hurt = true;
            hurtTimer = 10;
        }
    }
}
void Hurtbox::Draw()
{
    DrawRectangleLines(x,y,width,height,hurtColor);
}

//Getters
float Hurtbox::GetX() {return x;}
float Hurtbox::GetY() {return y;}
float Hurtbox::GetWidth() {return width;}
float Hurtbox::GetHeight() {return height;}