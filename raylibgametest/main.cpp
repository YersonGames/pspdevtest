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
#include <SDL3_mixer/SDL_mixer.h>


#include "Player.h"
#include "PlayerVariables.h"
#include "CollisionBlock.h"
#include "utils.h"
#include "Hitbox.h"
#include "Hurtbox.h"

PSP_MODULE_INFO("test", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    //Iniciar SDL,  audi
    if(SDL_Init(SDL_INIT_AUDIO) == false) 
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    //Iniciar Mixer
    if(MIX_Init() == false) {
        SDL_Log("Couldn't initialize SDL mixer: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    //Crear Mixer device
    MIX_Mixer* gMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

    //Cerar track
    MIX_Track* gSoundTrack = MIX_CreateTrack(gMixer);

    //Investigar como meter esta wea en allgun lado para llamarlo directamento, un array, lista, vector o la wea que sea
    MIX_Audio* FxHit = MIX_LoadAudio(gMixer,"assets/maincrahit.wav",true);

    //Setear ganancia, eso
    MIX_SetTrackGain(gSoundTrack, 1.0f);


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
            hurtbox->Update(hitboxes,gSoundTrack,FxHit);
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
