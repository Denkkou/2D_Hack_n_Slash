#pragma once
#include "SDL.h"

class AttackHitbox {
public:
	AttackHitbox(int x, int y, int w, int h) { 
		atk_posX = x;
		atk_posY = y;
		atk_width = w;
		atk_height = h;

		InitDebugBox();
	}

	int atk_posX;
	int atk_posY;
	int atk_width;
	int atk_height;
	bool atk_active;

	//debug box
	SDL_Rect hitBox;
	void InitDebugBox() {
		hitBox.x = atk_posX;
		hitBox.y = atk_posY;
		hitBox.w = atk_width;
		hitBox.h = atk_height;
	}
};