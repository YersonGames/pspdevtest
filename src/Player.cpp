#include <raylib.h>
#include <pspctrl.h>
#include <vector>
#include <cstdint>

#include "Player.h"
#include "PlayerVariables.h"
#include "utils.h"
#include "CollisionBlock.h"


Player::Player(float get_x, float get_y, float get_w, float get_h)
{
    x = get_x;
    y = get_y;
    width = get_w;
    height = get_h;
    jump = false;
    jumpKey = false;
}

void Player::Update(SceCtrlData& pad, SceCtrlData& padOld, PlayerVariables& playerVars, std::vector<CollisionBlock>& collisionBlocks)
{
    if (pad.Buttons & PSP_CTRL_RIGHT)
    {
        playerVars.hmove = 1;
    }
    else if (pad.Buttons & PSP_CTRL_LEFT)
    {
        playerVars.hmove = -1;
    }
    else
    {
        playerVars.hmove = 0;
    }

    x += (playerVars.hmove*playerVars.spd)*GetFrameTime();
    
    //Jump
    if ( (pad.Buttons & PSP_CTRL_CROSS) && !(padOld.Buttons & PSP_CTRL_CROSS) ) 
    {
        jumpKey = true;
    }
    if (jumpKey == true && jump == true)
    {
        playerVars.vmove = (-15.0f*30)*GetFrameTime();
        jumpKey = false;
    }

    //Gravity
    playerVars.vmove += playerVars.grav*GetFrameTime();

    //velocity limit gravity
    if (playerVars.vmove > (20.0f*30)*GetFrameTime() ) {playerVars.vmove = (20.0f*30)*GetFrameTime();}

    //Collision with CollisionBlock
    for (auto collisionBlock = collisionBlocks.begin(); collisionBlock != collisionBlocks.end(); collisionBlock++)
        {
            //Detect collision Vertical
            if (utils::getCollision(x,y+playerVars.vmove,width,height,*collisionBlock))
            {
                if (playerVars.vmove > 0)
                {
                    y = collisionBlock->GetY()-height;
                }
                else if (playerVars.vmove < 0)
                {
                    y = collisionBlock->GetY()-collisionBlock->GetHeight();
                }
                playerVars.vmove = 0;
            }

            //Detect floor y+1: Jump
            if (utils::getCollision(x,y+1,width,height,*collisionBlock))
            {
                jump = true;
            }
            else {jump = false;}
        }

    y += playerVars.vmove;

    padOld = pad;
}
void Player::Draw()
{
    DrawRectangle(x,y,width,height,LIME);
}

//Getters

float Player::GetX() {return x;}
float Player::GetY() {return y;}
float Player::GetWidth() {return width;}
float Player::GetHeight() {return height;}