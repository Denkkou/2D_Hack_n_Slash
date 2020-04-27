#include "Player.h"

Player::Player() {
	//initialise location and velocity
	posX = 800;
	posY = 450;
	velocity.X = 0;
	velocity.Y = 0;

	//initialise the sprite
	basicSprite.h = height;
	basicSprite.w = width;

	//set up other attributes
	health = 100;
	maxSpeed = 10;
	maxFallSpeed = 15;
	acceleration = 0;
	jumpStrength = 20;
	attackStrength = 0;
	weight = 1;

	//log creation of player
	SDL_Log("Player created");
}

Player::~Player(){ SDL_Log("Player destroyed"); }

void Player::Update() {
	//apply a constant downwards force
	velocity.Y += weight;

	//increment cooldown
	if(stateMachine.IS_GROUNDED)
		jumpCooldown++;

	//cooldown reset
	if (jumpCooldown >= 5)
		stateMachine.CAN_JUMP = true;

	//cap max fall
	if (velocity.Y + weight > maxFallSpeed)
		velocity.Y = maxFallSpeed;

	//idle check
	if (velocity.X != 0 || velocity.Y != 0)
		stateMachine.IS_IDLE = false;
	else {
		stateMachine.IS_IDLE = true;
	}

	//cap at maximum speed
	if (velocity.X > maxSpeed)
		velocity.X = maxSpeed;
	if (velocity.X < (-maxSpeed))
		velocity.X = (-maxSpeed);

	//apply values to vector and position
	velocity.X += acceleration;
	posX += velocity.X;
	posY += velocity.Y;

	//update basic sprite position
	basicSprite.x = posX;
	basicSprite.y = posY;

	SDL_Log("Player X %i Player Y %i", posX, posY);
}

void Player::Render(SDL_Renderer* aRenderer) {
	//sprite stuff here
	SDL_SetRenderDrawColor(aRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(aRenderer, &basicSprite);
}

//overridden commands
void Player::Jump() { //make variable
	if (stateMachine.IS_GROUNDED && stateMachine.CAN_JUMP) {
		stateMachine.IS_JUMPING = true;
		stateMachine.CAN_JUMP = false;
		velocity.Y -= jumpStrength;
		jumpCooldown = 0;
	}

	SDL_Log("Player Jump");
}

void Player::Attack() {
	SDL_Log("Player Attack");
}

void Player::MoveLeft() {
	acceleration = (-1);
	SDL_Log("Player Move Left");
}

void Player::MoveRight() {
	acceleration = 1;
	SDL_Log("Player Move Right");
}

void Player::MoveUpOnCollision(int yValueOfTerrain) {
	if (velocity.Y > 0) {
		posY = yValueOfTerrain - height;
		velocity.Y = 0;
	}
}