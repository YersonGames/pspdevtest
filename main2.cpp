#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <raylib.h>

PSP_MODULE_INFO("test", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

//SceCrtlData pad;

int main(void)
{
    InitWindow(480,272,"Hola");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Hola",0,0,16,WHITE);
            DrawRectangle(32,32,64,64,LIME);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
