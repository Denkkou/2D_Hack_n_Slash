#include "Pillar.h"

Pillar::Pillar(int posX, int posY, int width, int blockHeight) {
	//this is the hitbox used in collision
	X = posX;
	Y = posY;
	W = width;
	H = blockHeight;

	//init the block
	InitBlock(X, Y, W, blockHeight);
}

Pillar::~Pillar() {}

void Pillar::InitBlock(int x, int y, int w, int h) {
	//initialise the graphical block
	block.x = x;
	block.y = y;
	block.w = w;
	block.h = h;
}

void Pillar::Update() {}

void Pillar::Render(SDL_Renderer* aRenderer) {
	SDL_SetRenderDrawColor(aRenderer, 82, 122, 122, 255);
	SDL_RenderFillRect(aRenderer, &block);
}

