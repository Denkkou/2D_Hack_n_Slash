#include "Coin.h"

Coin::Coin(int cPosX, int cPosY) {
	//initialise at coordinates
	X = cPosX;
	Y = cPosY;

	//initialise sprite
	CoinSprite.Init(cPosX, cPosY, W, H);
}

Coin::~Coin(){}

void Coin::GetPickedUp() {
	//when called, move coin offscreen
	CoinSprite.MoveSprite(-50, -50);
	X = (-50);
	Y = (-50);
}

void Coin::Render(SDL_Renderer* aRenderer) {
	//load sprite (inefficient, load once then copy?)
	CoinSprite.Load(aRenderer, "./content/sprites/coinSprite.png");
	CoinSprite.Render(aRenderer);
}
