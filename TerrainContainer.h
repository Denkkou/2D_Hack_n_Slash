#ifndef aTerrainContainerFile
#define aTerrainContainerFile

#include <vector>
#include <iostream>
#include "SDL.h"
#include "Platform.h"
#include "Pillar.h"

class TerrainContainer {
public:
	TerrainContainer();
	~TerrainContainer();

	void AddPlatform(int posX, int posY, int width, int height);
	void AddPillar(int posX, int posY, int width, int height);

	void Update();
	void Render(SDL_Renderer* aRenderer);

	std::vector<TerrainObject*> aListOfPlatformObjects;
	std::vector<TerrainObject*> aListOfPillarObjects;
};

#endif