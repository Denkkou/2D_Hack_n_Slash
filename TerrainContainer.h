#ifndef aTerrainContainerFile
#define aTerrainContainerFile

#include <vector>
#include <iostream>
#include "SDL.h"
#include "TerrainObject.h"

class TerrainContainer {
public:
	TerrainContainer();
	~TerrainContainer();

	void AddObject(int posX, int posY, int width, int height);

	void Update();
	void Render(SDL_Renderer* aRenderer);

	std::vector<TerrainObject*> aListOfTerrainObjects;
};

#endif