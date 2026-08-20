#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Player.h"

int main(int argc, char* args[])
{
	(void)argc;
	(void)args;
	
	SDL_Window* gWindow = nullptr;
	SDL_Renderer* gRender = nullptr;
	
	if (SDL_Init(SDL_INIT_VIDEO) == false)
	{
		return 1;
	}
	
	gWindow = SDL_CreateWindow("Titulo",800,600,false);
	gRender = SDL_CreateRenderer(gWindow,nullptr);

	Player player({0,0,32,32});
	
	while (true)
	{
		player.Update();
		player.Draw(gRender);
		SDL_RenderPresent(gRender);
	}
	return 0;
}
