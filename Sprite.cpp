#include "Sprite.h"

Sprite::Sprite() {

}

Sprite::~Sprite() {
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

void Sprite::Init(int x, int y, int widthPixels, int heightPixels) {
	frameWidthPixels = widthPixels;
	frameHeightPixels = heightPixels;
	frameIndex = 0;

	srcRect.x = frameIndex * frameWidthPixels;
	srcRect.y = 0;
	srcRect.w = frameWidthPixels;
	srcRect.h = frameHeightPixels;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = frameWidthPixels;
	dstRect.h = frameHeightPixels;
}

void Sprite::Load(SDL_Renderer* renderer, const char* path, bool bUseColourKey) {
	texture = IMG_LoadTexture(renderer, path);
}


void Sprite::SetAnimationSpeed(unsigned int speed) {
	animationSpeed = speed;
}

void Sprite::Update(int ticks, int playerX, int playerY, int state, int facing) {
	dstRect.x = playerX;
	dstRect.y = playerY;

	faceDirection = facing; //left 2, right 3

	if (!isAnimating) {
		switch (state) {
		case 0: //walkLeft
			isAnimating = true;
			tempFrameCount = runningFrames;
			animationSequence = 1;
			//is flipped
			break;
		case 1: //walkRight
			isAnimating = true;
			tempFrameCount = runningFrames;
			animationSequence = 1;
			break;
		case 2: //idle
			tempFrameCount = idleFrames;
			animationSequence = 0;
			break;
		case 3: //jump
			isAnimating = true;
			animationSequence = 3;
			break;
		case 4: //attack
			isAnimating = true;
			animationSequence = 2;
			break;
		}
	}

	frameIndex = (ticks / animationSpeed) % tempFrameCount;

	//animation
	srcRect.x = frameIndex * frameWidthPixels;
	srcRect.y = animationSequence * frameHeightPixels;

	if (frameIndex == 0) {
		isAnimating = false;
	}
}

void Sprite::MoveSprite(int x, int y) {
	dstRect.x = x;
	dstRect.y = y;
}

void Sprite::Render(SDL_Renderer* renderer) {
	if (faceDirection == 2) //then flip
		SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
	else
		SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}
