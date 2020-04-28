#ifndef aPlayerCharacterFile
#define aPlayerCharacterFile

#include "GameActor.h"

class Player : public GameActor {
public:
	Player();
	~Player();

	virtual void Jump();
	virtual void Attack();
	virtual void MoveLeft();
	virtual void MoveRight();

	virtual void Update();
	virtual void Render(SDL_Renderer* aRenderer);

	int width = 48;
	int height = 64;
	int feetBoxOffset = 10;
	int jumpTicks;

	SDL_Rect playerHitbox;

	virtual void MoveUpOnCollision(int yValueOfTerrain);
	virtual void MoveSidewaysOnCollision(int xValueOfTerrain, int widthOfTerrain);
};

#endif