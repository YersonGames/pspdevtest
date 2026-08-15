#pragma once
#include <raylib.h>
#include <vector>

class Hitbox;

class Hurtbox
{
    public:
        float x;
        float y;
        float width;
        float height;
        float hurtTimer;
        Color hurtColor;

        bool hurt;

    Hurtbox(float get_x, float get_y, float get_w, float get_h);
    void Update(std::vector<Hitbox>& hitboxes);
    void Draw();

    //Getters
    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();
};