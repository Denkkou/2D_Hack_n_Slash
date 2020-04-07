#ifndef anInputHandlerFile
#define anInputHandlerFile

#include <iostream>
#include <SDL.h>
#include <functional>
#include <ctime>

#include "GameActor.h"

//declare command before input handler uses it
class Command;

//declare the input handler
class InputHandler {
public:
	std::function<void(GameActor&)> handleInput();
	SDL_Event _event;

	void bindCommands();
	bool getTime(char* buffer, int bufferSize);
private:
	//buttons
	std::function<void(GameActor&)> buttonX_;
	std::function<void(GameActor&)> buttonZ_;
	std::function<void(GameActor&)> buttonLeft_;
	std::function<void(GameActor&)> buttonRight_;
	std::function<void(GameActor&)> buttonEscape_;
	std::function<void(GameActor&)> buttonLShift_;
};

#endif