#include <raylib.h>
#include <pspctrl.h>

#include "Player.h"
#include "PlayerVariables.h"


Player::Player(float get_x, float get_y, float get_w, float get_h)
{
    x = get_x;
    y = get_y;
    width = get_w;
    height = get_h;
}

void Player::Update(SceCtrlData& pad, PlayerVariables& playerVars)
{
    sceCtrlReadBufferPositive(&pad, 1);


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
}
void Player::Draw()
{
    DrawRectangle(x,y,width,height,LIME);
}
