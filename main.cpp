#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <raylib.h>
#include <vector>

#include "Player.h"
#include "PlayerVariables.h"
#include "CollisionBlock.h"
#include "utils.h"

PSP_MODULE_INFO("test", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main(void)
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

    while (!WindowShouldClose())
    {
        sceCtrlReadBufferPositive(&pad, 1);

        //Player Update
        player.Update(pad,padOld,playerVars,collisionBlocks);

        //CollisionBlock Update
        for (auto collisionBlock = collisionBlocks.begin(); collisionBlock != collisionBlocks.end(); collisionBlock++)
        {
            collisionBlock->Update();
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

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
