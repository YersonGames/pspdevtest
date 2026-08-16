#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspaudio.h>
#include <pspaudiolib.h>
#include <pspuser.h>
#include <raylib.h>
#include <vector>


#include "Player.h"
#include "PlayerVariables.h"
#include "CollisionBlock.h"
#include "utils.h"
#include "Hitbox.h"
#include "Hurtbox.h"

PSP_MODULE_INFO("test", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main()
{
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
    CloseWindow();
    return 0;
}
