#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

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
	
	SDL_FRect square = {16,0,16,64};
	
	while (true)
	{
		SDL_SetRenderDrawColor(gRender,0,0,0,255);
		SDL_RenderClear(gRender);
		SDL_SetRenderDrawColor(gRender,255,255,255,255);
		SDL_RenderFillRect(gRender,&square);
		SDL_RenderPresent(gRender);
	}
	return 0;
}