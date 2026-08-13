#pragma once
#include <pspctrl.h>

#include "PlayerVariables.h"

class Player
{
public:
    float x;
    float y;
    float width;
    float height;

Player(float get_x, float get_y, float get_w, float get_h);
void Update(SceCtrlData& pad, PlayerVariables& playerVars);
void Draw();
};
