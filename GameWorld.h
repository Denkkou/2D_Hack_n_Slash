#ifndef aGameWorldFile
#define aGameWorldFile

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "InputHander.h"
#include "Player.h"
#include "FrameTimer.h"
#include "TerrainContainer.h"
#include "GetTime.h"

class GameWorld {
public:
	GameWorld();
	~GameWorld();

	SDL_Window* window;
	SDL_Renderer* renderer;

	InputHandler inputHandler;
	TerrainContainer terrainContainer;
	Player player;
	GetTime timeGetter;

	void Init();
	void Run();

	void Update();
	void Render();

	void Quit();
private:
	FrameTimer timer;
	const int DELTA_TIME = 16;
	bool done = false;

	//music and sfx
	Mix_Music* backgroundMusic = NULL;
	Mix_Chunk* attackSound = NULL;

	int sfxVolume = 128;
	int musicVolume = 32;

	bool detectedCollision(Player &player, TerrainObject* object);
};

#endif