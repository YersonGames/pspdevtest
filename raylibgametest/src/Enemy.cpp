#include <raylib.h>

#include "Enemy.h"

Enemy::Enemy(float get_x, float get_y, float get_w, float get_h)
{
	x = get_x;
	y = get_y;
	width = get_w;
	height = get_h;
}

void Enemy::Update()
{

}
void Enemy::Draw()
{
	DrawRectangle(x,y,width,height,ORANGE);
}