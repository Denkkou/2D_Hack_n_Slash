#include "Player.h"

Player::Player() {
	//initialise location and velocity
	posX = 800;
	posY = 450;
	velocity.X = 0;
	velocity.Y = 0;

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

	SDL_Log("Player X %i Player Y %i", posX, posY);
}

void Player::Render(SDL_Renderer* aRenderer) {
	//sprite stuff here
}

//overridden commands
void Player::Jump() {
	//count ticks since player was last grounded
	//if less than a certain number, keep adding upwards force
	//so long as Jump() is called

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

void Player::DoNothing(){
	if (velocity.X == 0)
		acceleration = 0;

	if (velocity.X < 0)
		acceleration = 1;

	if (velocity.X > 0)
		acceleration = (-1);
	SDL_Log("No Input");
}