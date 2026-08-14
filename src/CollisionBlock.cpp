#include <raylib.h>

#include "CollisionBlock.h"

CollisionBlock::CollisionBlock(float get_x, float get_y, float get_w, float get_h)
{
    x = get_x;
    y = get_y;
    width = get_w;
    height = get_h;
}

void CollisionBlock::Update()
{

}
void CollisionBlock::Draw()
{
    DrawRectangle(x,y,width,height,BLACK);
}

//Getters

float CollisionBlock::GetX() {return x;}
float CollisionBlock::GetY() {return y;}
float CollisionBlock::GetWidth() {return width;}
float CollisionBlock::GetHeight() {return height;}