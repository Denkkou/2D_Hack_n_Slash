#pragma once
#include "TerrainObject.h"

class Platform : public TerrainObject {
public:
	Platform(int posX, int posY, int width, int blockHeight);
	~Platform();

	virtual void InitBlock(int x, int y, int w, int h);

	virtual void Update();
	virtual void Render(SDL_Renderer* aRenderer);
};