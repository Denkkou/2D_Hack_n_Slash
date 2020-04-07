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
	//handle downwards force each frame
	velocity.Y += weight;

	//falling check
	if (velocity.Y > 0)
		stateMachine.IS_FALLING = true;
	else
		stateMachine.IS_FALLING = false;

	//idle check
	if (velocity.X == 0 && velocity.Y == 0) {
		acceleration = 0;
		stateMachine.IS_IDLE = true;
	}
	else {
		stateMachine.IS_IDLE = false;
	}
}

void Player::Render(SDL_Renderer* aRenderer) {

}

//overridden commands
void Player::Jump() {
	SDL_Log("Player Jump");
}

void Player::Attack() {
	SDL_Log("Player Attack");
}

void Player::MoveLeft() {
	SDL_Log("Player Move Left");
}

void Player::MoveRight() {
	SDL_Log("Player Move Right");
}
