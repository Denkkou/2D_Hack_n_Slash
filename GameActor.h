#ifndef aGameActorFile
#define aGameActorFile

#include <iostream>
#include <SDL.h>
#include "Vector2D.h"
#include "ActorStateMachine.h"

class GameActor {
public:
	GameActor() { SDL_Log("Game actor created"); }
	~GameActor() { SDL_Log("Game actor destroyed"); }

	virtual void Jump() = 0;
	virtual void Attack() = 0;
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;

	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* aRenderer) = 0;

	ActorStateMachine stateMachine;

	int health;
	int maxSpeed;
	int acceleration;
	int jumpStrength;
	int attackStrength;
	int weight;
	int maxFallSpeed;

	int jumpCooldown;

	int posX;
	int posY;
	Vector2D velocity;
};

#endif