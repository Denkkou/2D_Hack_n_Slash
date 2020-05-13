#include "ProgressBar.h"

ProgressBar::ProgressBar(){}
ProgressBar::~ProgressBar(){}

void ProgressBar::Init(int barX, int barY, int barW, int barH, int shThickness, int size) {
	decrementVal = barW / size;

	bar.x = barX;
	bar.y = barY;
	bar.w = barW;
	bar.h = barH;

	shadowBar.x = barX - shThickness;
	shadowBar.y = barY - shThickness;
	shadowBar.w = barW + (shThickness * 2);
	shadowBar.h = barH + (shThickness * 2);
}

void ProgressBar::Update(unsigned int counter) {
	//set width to ratio of counter
	bar.w = decrementVal * counter;

	g = 0 + (255 / 30) * counter;
	r = 255 - (255 / 30) * counter;
	b = 0;
}

void ProgressBar::Render(SDL_Renderer* aRenderer) {
	//draw shadow
	SDL_SetRenderDrawColor(aRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(aRenderer, &shadowBar);

	//draw bar
	SDL_SetRenderDrawColor(aRenderer, r, g, b, 255);
	SDL_RenderFillRect(aRenderer, &bar);
}
