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


#include "src/Player.h"
#include "src/PlayerVariables.h"
#include "src/CollisionBlock.h"
#include "src/utils.h"
#include "src/Hitbox.h"
#include "src/Hurtbox.h"
#include "src/Enemy.h"

PSP_MODULE_INFO("test", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    //Iniciar SDL,  audi
    if(SDL_Init(SDL_INIT_AUDIO) == false) 
    {
        return 1;
    }

    //Iniciar Mixer
    if(MIX_Init() == false)
	{
        return 2;
    }

    //Crear Mixer device
    MIX_Mixer* gMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

    //Crear track
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

    //Hurtbox test
    std::vector<Hurtbox> hurtboxes;
	
    //hurtboxes.push_back(Hurtbox(240+32,272-128,32,32,2.0f));
	
	//Enemy
	std::vector<Enemy> enemies;
	
	enemies.push_back(Enemy(240+32,272-128,32,32,{0.0f,0.0f,32.0f,32.0f}));

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
			
			//Enemy Draw
            for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
            {
                enemy->Draw();
            }

        EndDrawing();
    }
	
	collisionBlocks.clear();
	hitboxes.clear();
	hurtboxes.clear();

    MIX_Quit();
    CloseWindow();
    return 0;
}
