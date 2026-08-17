#pragma once
#include <raylib.h>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

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
		float hurtTimerDefault;

        bool hurt;

    Hurtbox(float get_x, float get_y, float get_w, float get_h, float get_hurtTimerDefault);
    void Update(std::vector<Hitbox>& hitboxes,MIX_Track* gSoundTrack, MIX_Audio* FxHit);
    void Draw();

    //Getters
    float GetX();
    float GetY();
    float GetWidth();
    float GetHeight();
};