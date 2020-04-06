#ifndef aGameWorldFile
#define aGameWorldFile

#include <iostream>
#include <SDL.h>

#include "InputHander.h"
#include "GameActor.h"

class GameWorld {
public:
	GameWorld();
	~GameWorld();

	SDL_Window* window;
	SDL_Renderer* renderer;

	InputHandler inputHandler;

	//this will need to be changed to a derived player subclass
	GameActor player;

	void Init();
	void Run();

	void Update();
	void Render();

	void Quit();
private:
	bool done = false;
};

#endif