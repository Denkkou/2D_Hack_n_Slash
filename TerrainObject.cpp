#include "TerrainObject.h"

TerrainObject::TerrainObject(int posX, int posY, int width,  int blockHeight) {

	X = posX;
	Y = posY;
	W = width;
	H = 10; //upper ledge

	//init the block
	InitBlock(X, Y, W, blockHeight);
}

TerrainObject::~TerrainObject() {
}

void TerrainObject::Update() {
}

void TerrainObject::Render(SDL_Renderer* aRenderer) {
	SDL_SetRenderDrawColor(aRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(aRenderer, &block);
}

void TerrainObject::InitBlock(int x, int y, int w, int h) {
	block.x = x;
	block.y = y;
	block.w = w;
	block.h = h;
}