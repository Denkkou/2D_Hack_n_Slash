#ifndef aTerrainObjectFile
#define aTerrainObjectFile

#include "SDL.h"

class TerrainObject {
public:
	TerrainObject() {}
	~TerrainObject() {};

	virtual void InitBlock(int x, int y, int w, int h) = 0;

	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* aRenderer) = 0;

	int X;
	int Y;
	int W;
	int H;

	SDL_Rect block;
};

#endif