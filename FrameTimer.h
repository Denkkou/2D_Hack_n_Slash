#ifndef aFrameTimerFile
#define aFrameTimerFile

#include <iostream>
#include <SDL.h>

class FrameTimer {
public:
	FrameTimer();

	void resetTicks();
	int getTicks();
private:
	int startTicks;
};

#endif