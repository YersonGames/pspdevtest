#pragma once
#include <pspctrl.h>
#include <vector>
#include <cstdint>

#include "PlayerVariables.h"

class CollisionBlock;

class Player
{
    public:
        float x;
        float y;
        float width;
        float height;
        bool jump;
        bool jumpKey;

    Player(float get_x, float get_y, float get_w, float get_h);
    void Update(SceCtrlData& pad, SceCtrlData& padOld, PlayerVariables& playerVars, std::vector<CollisionBlock>& collisionBlocks);
    void Draw();

    //Getters
    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();
};
