#ifndef anInputHandlerFile
#define anInputHandlerFile

#include <iostream>
#include <SDL.h>
#include <functional>
#include <ctime>

#include "Player.h"

//declare command before input handler uses it
class Command;

//declare the input handler
class InputHandler {
public:
	//pass it a reference to the loop control (maybe replace with game state object)
	void HandleInput(bool& done, GameActor& player);
	SDL_Event _event;
private:
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
};

#endif