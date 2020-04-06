#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "GameWorld.h"

GameWorld gameWorld;

int main(int argc, char* argvp[]) {
	//initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { return 1; }
	else { SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init failed!"); }

	//initialise SDL_image
	if (IMG_Init(SDL_INIT_EVERYTHING) < 0) { return 1; }
	else { SDL_LogError(SDL_LOG_CATEGORY_ERROR, "IMG_Init failed!"); }

	//initialise and run gameworld
	gameWorld.Init();
	gameWorld.Run();

	//quit
	IMG_Quit();
	SDL_Quit();
	return 0;
}