#include "FrameTimer.h"

FrameTimer::FrameTimer() {
	startTicks = 0;
}

void FrameTimer::resetTicks() {
	startTicks = SDL_GetTicks();
}

int FrameTimer::getTicks() {
	return (SDL_GetTicks() - startTicks);
}