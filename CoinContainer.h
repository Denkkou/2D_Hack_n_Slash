#ifndef aCoinContainerFile
#define aCoinContainerFile

#include <vector>
#include "SDL.h"
#include "Coin.h"

class CoinContainer {
public:
	CoinContainer();
	~CoinContainer();

	void AddCoin(int posX, int posY);
	void Render(SDL_Renderer* aRenderer);

	std::vector<Coin*> aListOfCoins;
};

#endif
