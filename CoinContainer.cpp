#include "CoinContainer.h"

CoinContainer::CoinContainer() {
	SDL_Log("GameWorld.h          | Coin Container Created");

	//create coin spread
	AddCoin(40, 360);
	AddCoin(136, 360);
	AddCoin(40, 660);
	AddCoin(136, 660);
	AddCoin(85, 800);
	AddCoin(260, 530);

	AddCoin(530, 530);
	AddCoin(380, 630);
	AddCoin(380, 300);
	AddCoin(380, 160);
	AddCoin(500, 800);

	//tower
	AddCoin(700, 800);
	AddCoin(700, 700);
	AddCoin(700, 600);
	AddCoin(700, 500);

	//arc
	AddCoin(780, 400);
	AddCoin(870, 300);
	AddCoin(990, 260);
	AddCoin(1100, 300);
	AddCoin(1170, 400);

	//bottom right corner
	AddCoin(1340, 800);
	AddCoin(1440, 800);
	AddCoin(1340, 700);
	AddCoin(1440, 700);

	//upper right platform
	AddCoin(1340, 400);
	AddCoin(1440, 400);
	AddCoin(1340, 300);
	AddCoin(1440, 300);

	AddCoin(900, 800);
	AddCoin(900, 650);
}

CoinContainer::~CoinContainer() {
	//clear memory
	for (auto& element : aListOfCoins) {
		delete element;
	}

	SDL_Log("GameWorld.h          | Coin Container Destroyed");
}

void CoinContainer::AddCoin(int posX, int posY) {
	Coin* aCoin = new Coin(posX, posY);
	this->aListOfCoins.push_back(aCoin);
}

void CoinContainer::Render(SDL_Renderer* aRenderer) {
	for (auto& element : aListOfCoins) {
		element->Render(aRenderer);
	}
}

