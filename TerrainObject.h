#ifndef aTerrainObjectFile
#define aTerrainObjectFile

#include "SDL.h"

class TerrainObject {
public:
	TerrainObject(int posX, int posY, int width, int height);
	~TerrainObject();

	void Update();
	void Render(SDL_Renderer* aRenderer);
	void Collision();

	SDL_Rect block;
};

#endif