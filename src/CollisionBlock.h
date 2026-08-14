#pragma once

class CollisionBlock
{
    public:
        float x;
        float y;
        float width;
        float height;

    CollisionBlock(float get_x, float get_y, float get_w, float get_h);
    void Update();
    void Draw();
    
    //Getters
    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();
};