#pragma once

namespace utils
{   
    bool getCollision(float get_x,float get_y, float get_w, float get_h, auto& obj)
    {
        if (get_x+get_w > obj.GetX() && get_x < obj.GetY()+obj.GetWidth() && get_y+get_h > obj.GetY() && get_y < obj.GetY()+obj.GetHeight() )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}