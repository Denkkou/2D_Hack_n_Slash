#ifndef aTerrainObjectFile
#define aTerrainObjectFile

#include "SDL.h"

class TerrainObject {
public:
	TerrainObject(int posX, int posY, int width, int blockHeight);
	~TerrainObject();

	void InitBlock(int x, int y, int w, int h);

	void Update();
	void Render(SDL_Renderer* aRenderer);

	int X;
	int Y;
	int W;
	int H;

	SDL_Rect block;
};

#endif