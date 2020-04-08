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
	//pass it a reference to the loop control (maybe replace with game state object)
	std::function<void(GameActor&)> handleInput(bool& done);
	SDL_Event _event;

	void bindCommands();
	bool getTime(char* buffer, int bufferSize);
private:
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	//buttons
	std::function<void(GameActor&)> buttonX_;
	std::function<void(GameActor&)> buttonZ_;
	std::function<void(GameActor&)> buttonLeft_;
	std::function<void(GameActor&)> buttonRight_;
	std::function<void(GameActor&)> buttonEscape_;
	std::function<void(GameActor&)> buttonLShift_;
};

#endif