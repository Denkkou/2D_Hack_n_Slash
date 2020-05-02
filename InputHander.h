#ifndef anInputHandlerFile
#define anInputHandlerFile

#include <iostream>
#include <SDL.h>
#include <functional>
#include <ctime>

#include "Player.h"
#include "GetTime.h"

//declare command before input handler uses it
class Command;

//declare the input handler
class InputHandler {
public:
	//pass it a reference to the loop control, player, and time getter
	void HandleInput(bool& done, GameActor& player, GetTime& timeGetter);
	SDL_Event _event;
private:
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
};

#endif