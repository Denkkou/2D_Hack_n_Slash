#include "Player.h"

Player::Player() {
	//initialise location and velocity
	posX = 800;
	posY = 450;
	velocity.X = 0;
	velocity.Y = 0;

	//initialise the sprite
	playerHitbox.h = height;
	playerHitbox.w = width;

	//default facing
	stateMachine.IS_FACING_LEFT = true;

	//set up other attributes
	health = 100;
	maxSpeed = 10;
	maxFallSpeed = 15;
	acceleration = 0;
	jumpStrength = 15;
	attackStrength = 0;
	weight = 1;

	attackCooldown = 0;
	attackRange = 45;
	attackDuration = 25;

	//create the four attack hitboxes
	AttackHitbox* atk_up = new AttackHitbox(posX, posY - attackRange, width, attackRange);
	this->attackHitboxes.push_back(atk_up);
	AttackHitbox* atk_down = new AttackHitbox(posX, posY + height, width, attackRange);
	this->attackHitboxes.push_back(atk_down);
	AttackHitbox* atk_left = new AttackHitbox(posX - attackRange, posY, attackRange, height);
	this->attackHitboxes.push_back(atk_left);
	AttackHitbox* atk_right = new AttackHitbox(posX + width, posY, attackRange, height);
	this->attackHitboxes.push_back(atk_right);

	//log creation of player
	SDL_Log("Player created");
}

Player::~Player() { 
	//destroy attack hitboxes
	for (auto& element : attackHitboxes) {
		delete element;
	}

	SDL_Log("Player destroyed"); 
}

void Player::Update() {
	//apply a constant downwards force
	velocity.Y += weight;

	//------------------------------------------------------------------------- ATTACKING
	//check for attack, start duration
	if (stateMachine.IS_ATTACKING && attackCooldown >= 20 && !startAttackDuration) {
		startAttackDuration = true;
		direction = CalculateDirection();
	}

	if (startAttackDuration) {
		ticksSinceAttackStart++;

		if (ticksSinceAttackStart <= attackDuration)
			Attack();
		else {
			ticksSinceAttackStart = 0;
			startAttackDuration = false;
			attackCooldown = 0;
		}
	}
	else {
		//reset direction to facing
		if (stateMachine.IS_FACING_LEFT) direction = LEFT;
		else direction = RIGHT;

		//deactivate hitboxes
		for (auto& element : attackHitboxes) {
			element->atk_active = false;
		}
	}

	attackCooldown++;

	//------------------------------------------------------------------------- JUMPING PHYSICS
	//check for jump
	if (stateMachine.IS_JUMPING)
		Jump();

	//increment jumping cooldown, reset variable jump
	if (stateMachine.IS_GROUNDED) {
		jumpTicks = 5;
		jumpCooldown++;
	}
	else if (stateMachine.IS_JUMPING && jumpTicks > 0) {
		//if still held & ticks remain, boost upward velocity
		velocity.Y -= 1;
		jumpTicks--;
	}
	else
		jumpTicks = 0;

	//cooldown reset
	if (jumpCooldown >= 5)
		stateMachine.CAN_JUMP = true;

	//------------------------------------------------------------------------- MOVEMENT PHYSICS
	//cap max fall
	if (velocity.Y + weight > maxFallSpeed)
		velocity.Y = maxFallSpeed;

	//idle check for animations
	if (velocity.X != 0 || velocity.Y != 0)
		stateMachine.IS_IDLE = false;
	else 
		stateMachine.IS_IDLE = true;

	//cap at maximum speed
	if (velocity.X > maxSpeed)
		velocity.X = maxSpeed;
	if (velocity.X < (-maxSpeed))
		velocity.X = (-maxSpeed);

	//------------------------------------------------------------------------- UPDATING POSITIONS
	//apply values to vector and position
	velocity.X += acceleration;
	posX += velocity.X;
	posY += velocity.Y;

	//move attack hitboxes with the player
	UpdateHitboxPositions();

	//update basic sprite position
	playerHitbox.x = posX;
	playerHitbox.y = posY;
}

//this is very verbose and clunky, find an iterative approach
void Player::UpdateHitboxPositions() {
	//too verbose? is an iterative approach possible?
	attackHitboxes[0]->atk_posX = posX;
	attackHitboxes[0]->atk_posY = posY - attackRange;

	attackHitboxes[1]->atk_posX = posX;
	attackHitboxes[1]->atk_posY = posY + height;

	attackHitboxes[2]->atk_posX = posX - attackRange;
	attackHitboxes[2]->atk_posY = posY;

	attackHitboxes[3]->atk_posX = posX + width;
	attackHitboxes[3]->atk_posY = posY;

	//debug rendering, clunky, I know...
	attackHitboxes[0]->hitBox.x = posX;
	attackHitboxes[0]->hitBox.y = posY - attackRange;
	attackHitboxes[1]->hitBox.x = posX;
	attackHitboxes[1]->hitBox.y = posY + height;
	attackHitboxes[2]->hitBox.x = posX - attackRange;
	attackHitboxes[2]->hitBox.y = posY;
	attackHitboxes[3]->hitBox.x = posX + width;
	attackHitboxes[3]->hitBox.y = posY;
}

void Player::Render(SDL_Renderer* aRenderer) {
	//sprite stuff here
	SDL_SetRenderDrawColor(aRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(aRenderer, &playerHitbox);

	//debug rendering of hitboxes
	for (auto& element : attackHitboxes) {
		if (element->atk_active) SDL_SetRenderDrawColor(aRenderer, 255, 0, 0, 255);
		else SDL_SetRenderDrawColor(aRenderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(aRenderer, &element->hitBox);
	}
}

//commands
void Player::Jump() { //make variable
	if (stateMachine.IS_GROUNDED && stateMachine.CAN_JUMP) {
		stateMachine.CAN_JUMP = false;
		velocity.Y -= jumpStrength;
		jumpCooldown = 0;
	}

	SDL_Log("Player Jump");
}

void Player::Attack() {
	//reset hitboxes
	for (auto& element : attackHitboxes) {
		element->atk_active = false;
	}

	attackHitboxes[direction]->atk_active = true;

	SDL_Log("Player Attack");
}

int Player::CalculateDirection() {
	if (stateMachine.IS_AIMING_UP) return UP;
	if (stateMachine.IS_AIMING_DOWN) return DOWN;
	if (stateMachine.IS_FACING_LEFT) return LEFT;
	if (stateMachine.IS_FACING_RIGHT) return RIGHT;

	//return a default value
	return lastFacing;
}

void Player::MoveLeft() {
	stateMachine.IS_FACING_RIGHT = false;
	stateMachine.IS_FACING_LEFT = true;
	stateMachine.IS_AIMING_UP = false;
	stateMachine.IS_AIMING_DOWN = false;

	lastFacing = LEFT;
	acceleration = (-1);
	SDL_Log("Player Facing: %d", stateMachine.IS_FACING_RIGHT);
}

void Player::MoveRight() {
	stateMachine.IS_FACING_RIGHT = true;
	stateMachine.IS_FACING_LEFT = false;
	stateMachine.IS_AIMING_UP = false;
	stateMachine.IS_AIMING_DOWN = false;

	lastFacing = RIGHT;
	acceleration = 1;
	SDL_Log("Player Facing: %d", stateMachine.IS_FACING_RIGHT);
}

//collision response
void Player::MoveUpOnCollision(int yValueOfTerrain) {
	if (velocity.Y > 0 && posY < yValueOfTerrain) {
		posY = yValueOfTerrain - height;
		velocity.Y = 0;

		//handle flags
		stateMachine.IS_GROUNDED = true;
		stateMachine.IS_JUMPING = false;
	}
}

void Player::MoveSidewaysOnCollision(int xValueOfTerrain, int widthOfTerrain) {
	if (posX <= xValueOfTerrain)
		posX = (xValueOfTerrain - width);
	else
		posX = (xValueOfTerrain + widthOfTerrain);

	velocity.X = 0;
}
