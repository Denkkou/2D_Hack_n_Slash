#ifndef aCoinFile
#define aCoinFile

#include "Sprite.h"

class Coin {
public:
	Coin(int cPosX, int cPosY);
	~Coin();

	void GetPickedUp();
	void Render(SDL_Renderer* aRenderer);

	Sprite CoinSprite;

	int X;
	int Y;
	int W = 28;
	int H = 35;
};

#endif