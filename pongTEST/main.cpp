#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <pspctrl.h>

#include "Player.h"
#include "Ball.h"

#include "gameutils.h"

int main(int argc, char* args[])
{
	(void)argc;
	(void)args;
	
	SceCtrlData pad;
	
	sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	SDL_Window* gWindow = nullptr;
	SDL_Renderer* gRender = nullptr;
	
	if (SDL_Init(SDL_INIT_VIDEO) == false)
	{
		return 1;
	}
	
	gWindow = SDL_CreateWindow("Titulo",800,600,false);
	gRender = SDL_CreateRenderer(gWindow,nullptr);
	
	SDL_SetRenderVSync(gRender,1);

	Player player({16,136-24,8,48});
	Ball ball({240-4,136-4,8,8});
	Enemy enemy({480-16,136-24,9,48});
	
	while (true)
	{
		sceCtrlReadBufferPositive(&pad, 1);
		
		SDL_SetRenderDrawColor(gRender,0,0,0,255);
		SDL_RenderClear(gRender);
		
		player.Update(pad);
		player.Draw(gRender);
		
		ball.Update();
		ball.Draw(gRender);
		
		enemy.Update(pad);
		enemy.Draw(gRender);
		
		SDL_RenderLine(gRender,0,0,480,0);
		SDL_RenderLine(gRender,0,271,480,271);
		
		SDL_RenderPresent(gRender);
	}
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRender);
	SDL_Quit();
	return 0;
}
