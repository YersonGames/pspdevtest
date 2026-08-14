#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <raylib.h>

#include "Player.h"
#include "PlayerVariables.h"

PSP_MODULE_INFO("test", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

//SceCrtlData pad;

int main(void)
{
    InitWindow(480,272,"Hola");
    SetTargetFPS(30);

    SceCtrlData pad;
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    //Create Player
    Player player(32.0f,32.0f,32.0f,32.0f);
    PlayerVariables playerVars;
    playerVars.hmove = 0.0f;
    playerVars.vmove = 0.0f;
    playerVars.spd = 10.0f*30;
    playerVars.grav = 1.0f*30;

    while (!WindowShouldClose())
    {
        player.Update(pad,playerVars);
        BeginDrawing();
            ClearBackground(WHITE);
            DrawText(TextFormat("Hola: %s",RAYLIB_VERSION),0,0,16,BLACK);
            DrawFPS(0,16);
            player.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
