#ifndef aProgressBarFile
#define aProgressBarFile

#include <SDL.h>

class ProgressBar {
public:
	ProgressBar();
	~ProgressBar();

	void Init(int barX, int barY, int barW, int barH, int shThickness, int size);
	void Update(unsigned int counter);
	void Render(SDL_Renderer* aRenderer);

	SDL_Rect bar;
	SDL_Rect shadowBar;
	int decrementVal;

	int r, g, b;
};

#endif