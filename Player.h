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
};

#endif