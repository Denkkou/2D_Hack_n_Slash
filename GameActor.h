#ifndef aGameActorFile
#define aGameActorFile

#include <iostream>
#include <SDL.h>
#include <vector>
#include "Vector2D.h"
#include "ActorStateMachine.h"
#include "AttackHitbox.h"
#include "GetTime.h"

class GameActor {
public:
	GameActor() { SDL_Log("Game actor created"); }
	~GameActor() { SDL_Log("Game actor destroyed"); }

	virtual void Jump() = 0;
	virtual void Attack() = 0;
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;

	virtual void Update(GetTime& timeGetter) = 0;
	virtual void UpdateHitboxPositions() = 0;
	virtual void Render(SDL_Renderer* aRenderer) = 0;

	virtual void MoveUpOnCollision(int yValueOfTerrain) = 0;
	virtual void MoveSidewaysOnCollision(int xValueOfTerrain, int widthOfTerrain) = 0;

	ActorStateMachine stateMachine;
	std::vector<AttackHitbox*> attackHitboxes;

	int health;
	int maxSpeed;
	int acceleration;
	int jumpStrength;
	int attackStrength;
	int weight;
	int maxFallSpeed;
	int attackRange;

	int animationState;

	int jumpCooldown;
	int attackCooldown;
	int attackDuration;

	enum aimDirections {UP, DOWN, LEFT, RIGHT};
	virtual int CalculateDirection() = 0;
	int lastFacing;

	int posX;
	int posY;
	Vector2D velocity;
};

#endif