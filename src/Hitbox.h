#pragma once

class Hitbox
{
    public:
        float x;
        float y;
        float width;
        float height;
        float frameTimer;
        bool destroy;
    
    Hitbox(float get_x, float get_y, float get_w, float get_h, float get_frameTimer);
    void Update();
    void Draw();

    //Getters
    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();
    bool GetDestroy();
};