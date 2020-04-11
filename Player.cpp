#include "Player.h"

Player::Player() {
	//initialise location and velocity
	posX = 800;
	posY = 450;
	velocity.X = 0;
	velocity.Y = 0;

	//initialise the sprite
	basicSprite.h = 64;
	basicSprite.w = 48;

	//set up other attributes
	health = 100;
	maxSpeed = 10;
	acceleration = 0;
	jumpStrength = 20;
	attackStrength = 0;
	weight = 1;

	//log creation of player
	SDL_Log("Player created");
}

Player::~Player(){ SDL_Log("Player destroyed"); }

//using a player state machine to handle player state - maybe try events?
void Player::Update() {
	//apply a constant downwards force
	velocity.Y += weight;

	//temporary floor
	if (posY > 800) {
		posY = 800;
		velocity.Y = 0;
		stateMachine.IS_GROUNDED = true;
		stateMachine.IS_JUMPING = false;
	}
	else {
		stateMachine.IS_GROUNDED = false;
	}

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
	if (stateMachine.IS_GROUNDED) {
		stateMachine.IS_JUMPING = true;
		velocity.Y -= jumpStrength;
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
