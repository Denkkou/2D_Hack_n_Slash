#include "Platform.h"

Platform::Platform(int posX, int posY, int width, int blockHeight) {
	//this is the hitbox used in collision
	X = posX;
	Y = posY;
	W = width;
	H = 10; //upper ledge

	//init the block
	InitBlock(X, Y, W, blockHeight);
}

Platform::~Platform() {}

void Platform::InitBlock(int x, int y, int w, int h) {
	//initialise the graphical block
	block.x = x;
	block.y = y;
	block.w = w;
	block.h = h;
}

void Platform::Update() {}

void Platform::Render(SDL_Renderer* aRenderer) {
	SDL_SetRenderDrawColor(aRenderer, 200, 100, 0, 255);
	SDL_RenderFillRect(aRenderer, &block);
}

