#ifndef aPlayerCharacterFile
#define aPlayerCharacterFile

#include "GameActor.h"
#include "Sprite.h"

class Player : public GameActor {
public:
	Player();
	~Player();

	enum playerStates {walkLeft, walkRight, idle, jump, attack};

	virtual void Jump();
	virtual void Attack();
	virtual void MoveLeft();
	virtual void MoveRight();

	virtual void Update(GetTime& timeGetter);
	virtual void UpdateHitboxPositions();
	virtual void Render(SDL_Renderer* aRenderer);

	int width = 64;
	int height = 64;
	int feetBoxOffset = 10;
	int jumpTicks;

	int direction;
	int ticksSinceAttackStart = 0;
	bool startAttackDuration;

	Sprite playerSprite;
	SDL_Rect playerHitbox;

	bool DEBUG = false;

	virtual int CalculateDirection();

	virtual void MoveUpOnCollision(int yValueOfTerrain);
	virtual void MoveSidewaysOnCollision(int xValueOfTerrain, int widthOfTerrain);
};

#endif