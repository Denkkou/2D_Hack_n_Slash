#include "TerrainObject.h"

TerrainObject::TerrainObject(int posX, int posY, int width, int height) {
	//create the block
	block.x = posX;
	block.y = posY;
	block.w = width;
	block.h = height;
}

TerrainObject::~TerrainObject() {
}

void TerrainObject::Update() {
}

void TerrainObject::Render(SDL_Renderer* aRenderer) {
	SDL_SetRenderDrawColor(aRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(aRenderer, &block);
}

void TerrainObject::Collision() {

}
