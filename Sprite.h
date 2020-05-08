#ifndef aSpriteFile
#define aSpriteFile

#include "SDL.h"
#include "SDL_image.h"

class Sprite {
public:
	Sprite();
	~Sprite();

	void Init(int x, int y, int widthPixels, int heightPixels);
	void Load(SDL_Renderer* renderer, const char* path, bool bUseColourKey = false);

	void SetAnimationSpeed(unsigned int speed);

	void Update(int ticks, int playerX, int playerY, int state, int facing);
	void Render(SDL_Renderer* renderer);

	int faceDirection;
	int x, y = 0;
	int frameWidthPixels, frameHeightPixels = 0;
	int xScale, yScale = 1;
protected:
	SDL_Texture* texture = nullptr;
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	unsigned int tempFrameCount = 1;
	unsigned int animationSequence = 0;

	unsigned int idleFrames = 6;
	unsigned int runningFrames = 4;
	unsigned int jumpingFrames = 5;
	unsigned int attackFrames = 4;

	bool isAnimating;
	unsigned int animationSpeed = 80;
	unsigned int frameIndex;
};

#endif