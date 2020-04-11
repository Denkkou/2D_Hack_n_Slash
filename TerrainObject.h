#ifndef aTerrainObjectFile
#define aTerrainObjectFile

#include "SDL.h"

class TerrainObject {
public:
	TerrainObject();
	~TerrainObject();

	void Update();
	void Render(SDL_Renderer* aRenderer);
	void Collision();

	int blockPosX;
	int blockPosY;
	int blockWidth;
	int blockHeight;
};

#endif