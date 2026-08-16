#include <raylib.h>
#include <pspctrl.h>
#include <vector>
#include <cstdint>

#include "Player.h"
#include "PlayerVariables.h"
#include "utils.h"
#include "CollisionBlock.h"
#include "Hitbox.h"


Player::Player(float get_x, float get_y, float get_w, float get_h)
{
    x = get_x;
    y = get_y;
    width = get_w;
    height = get_h;
    jump = false;
    jumpKey = false;
    int8_t hDir = 1;
}

void Player::Update(SceCtrlData& pad, SceCtrlData& padOld, PlayerVariables& playerVars, std::vector<CollisionBlock>& collisionBlocks, std::vector<Hitbox>& hitboxes)
{
    if (pad.Buttons & PSP_CTRL_RIGHT)
    {
        playerVars.hmove = 1;
        hDir = 1;
    }
    else if (pad.Buttons & PSP_CTRL_LEFT)
    {
        playerVars.hmove = -1;
        hDir = -1;
    }
    else
    {
        playerVars.hmove = 0;
    }
    
    //Jump
    if ( (pad.Buttons & PSP_CTRL_CROSS) && !(padOld.Buttons & PSP_CTRL_CROSS) ) 
    {
        jumpKey = true;
    }
    if (jumpKey == true && jump == true && (pad.Buttons & PSP_CTRL_CROSS))
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
            //Detect Vertical collision
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

            //Detect Horizontal collision 
            if (utils::getCollision(x+(playerVars.hmove*playerVars.spd)*GetFrameTime(),y,width,height,*collisionBlock))
            {
                if (playerVars.hmove > 0)
                {
                    x = collisionBlock->GetX()-width;
                }
                else if (playerVars.hmove < 0)
                {
                    x = collisionBlock->GetX()-collisionBlock->GetWidth();
                }
                playerVars.hmove = 0;
            }
        }

    //detect jump
    if (playerVars.vmove == 0){jump = true;}
    else {jump = false;}

    x += (playerVars.hmove*playerVars.spd)*GetFrameTime();
    y += playerVars.vmove;

    //Create Hitbox test
    if ( (pad.Buttons & PSP_CTRL_CIRCLE) && !(padOld.Buttons & PSP_CTRL_CIRCLE) ) 
    {
        hitboxes.push_back(Hitbox(x+(32*hDir),y+8,32,16,2));
    }

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