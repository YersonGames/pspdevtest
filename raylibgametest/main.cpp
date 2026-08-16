#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspaudio.h>
#include <pspaudiolib.h>
#include <pspuser.h>
#include <raylib.h>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>


#include "Player.h"
#include "PlayerVariables.h"
#include "CollisionBlock.h"
#include "utils.h"
#include "Hitbox.h"
#include "Hurtbox.h"

//PSP_MODULE_INFO("test", 0, 1, 0);
//PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    if(SDL_Init(SDL_INIT_AUDIO) == false) 
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if(MIX_Init() == false) {
        SDL_Log("Couldn't initialize SDL mixer: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    MIX_Track* sound_track = MIX_CreateTrack(mixer);

    MIX_Audio* FxHit = MIX_LoadAudio(mixer,"assets/maincrahit.wav",true);
    if (!FxHit) {
        SDL_Log("Couldn't load audio file: %s", SDL_GetError());
        MIX_DestroyMixer(mixer);
        MIX_Quit();
        SDL_Quit();
        return 5;
    }

    MIX_SetTrackAudio(sound_track,FxHit);
    MIX_SetTrackGain(sound_track, 1.0f);


    InitWindow(480,272,"Hola");
    SetTargetFPS(30);

    SceCtrlData pad;
    SceCtrlData padOld;
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    //Create Player
    Player player(32.0f,32.0f,32.0f,32.0f);
    PlayerVariables playerVars;
    playerVars.hmove = 0.0f;
    playerVars.vmove = 0.0f;
    playerVars.spd = 10.0f*30;
    playerVars.grav = 1.0f*30;

    //Collision Blocks
    std::vector<CollisionBlock> collisionBlocks;
    collisionBlocks.push_back(CollisionBlock(0,272-48,480,32));
    collisionBlocks.push_back(CollisionBlock(240,272-48-32,240,32));
    collisionBlocks.push_back(CollisionBlock(240+128,272-48-128,240,128));

    //Hitbox test
    std::vector<Hitbox> hitboxes;
    hitboxes.push_back(Hitbox(128,64,64,64,10.0f));
    hitboxes.push_back(Hitbox(128+64,64,64,64,20.0f));

    //Hurtbox test
    std::vector<Hurtbox> hurtboxes;
    hurtboxes.push_back(Hurtbox(240+32,272-128,32,32));

    MIX_PlayAudio(mixer,FxHit);

    while (!WindowShouldClose())
    {
        sceCtrlReadBufferPositive(&pad, 1);

        //Player Update
        player.Update(pad,padOld,playerVars,collisionBlocks,hitboxes);

        //CollisionBlock Update
        for (auto collisionBlock = collisionBlocks.begin(); collisionBlock != collisionBlocks.end(); collisionBlock++)
        {
            collisionBlock->Update();
        }

        //Hitbox Update
        for (auto hitbox = hitboxes.begin(); hitbox != hitboxes.end();)
        {
            if (hitbox->GetDestroy() == true)
            {
                hitboxes.erase(hitbox);
            }
            else
            {
                hitbox->Update();
                hitbox++;
            }
        }

        //Hurtbox Update test
        for (auto hurtbox = hurtboxes.begin(); hurtbox != hurtboxes.end(); hurtbox++)
        {
            hurtbox->Update(hitboxes);
        }

        BeginDrawing();
            ClearBackground(WHITE);
            DrawText(TextFormat("Hola: %s",RAYLIB_VERSION),0,0,16,BLACK);
            DrawFPS(0,16);

            //Player Update
            player.Draw();

            //CollisionBlock Update
            for (auto collisionBlock = collisionBlocks.begin(); collisionBlock != collisionBlocks.end(); collisionBlock++)
            {
                collisionBlock->Draw();
            }

            //Hitbox Draw
            for (auto hitbox = hitboxes.begin(); hitbox != hitboxes.end(); hitbox++)
            {
                hitbox->Draw();
            }

            //Hurtbox Draw
            for (auto hurtbox = hurtboxes.begin(); hurtbox != hurtboxes.end(); hurtbox++)
            {
                hurtbox->Draw();
            }

        EndDrawing();
    }
    MIX_Quit();
    CloseWindow();
    return 0;
}
