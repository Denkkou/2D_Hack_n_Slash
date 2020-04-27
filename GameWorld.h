#ifndef aGameWorldFile
#define aGameWorldFile

#include <iostream>
#include <SDL.h>

#include "InputHander.h"
#include "Player.h"
#include "FrameTimer.h"
#include "TerrainContainer.h"

class GameWorld {
public:
	GameWorld();
	~GameWorld();

	SDL_Window* window;
	SDL_Renderer* renderer;

	InputHandler inputHandler;
	TerrainContainer terrainContainer;
	Player player;

	void Init();
	void Run();

	void Update();
	void Render();

	void Quit();
private:
	FrameTimer timer;
	const int DELTA_TIME = 16;
	bool done = false;

	bool detectedCollision(Player &player, TerrainObject* object);
};

#endif