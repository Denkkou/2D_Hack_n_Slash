#pragma once
#include "TerrainObject.h"

class Pillar : public TerrainObject {
public:
	Pillar(int posX, int posY, int width, int blockHeight);
	~Pillar();

	virtual void InitBlock(int x, int y, int w, int h);

	virtual void Update();
	virtual void Render(SDL_Renderer* aRenderer);
};