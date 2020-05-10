#include "InputHander.h"

//needs SDL quit code and a way of handling escape
void InputHandler::HandleInput(bool& done, GameActor& player, GetTime& timeGetter, SDL_Window* window) {
    //event polling
    while (SDL_PollEvent(&_event)) {
        //timestamp
        SDL_Keycode keyPressed = _event.key.keysym.sym;
        char timestr[32];
        timeGetter.getTime(timestr, 32);

        //log a key down
        if (_event.type == SDL_KEYDOWN && !_event.key.repeat)
            SDL_Log("[%s] [KEY DOWN] | time %d;  char %s; (InputHandler.cpp)", timestr, _event.key.timestamp, SDL_GetKeyName(keyPressed));

        //log a key up
        if (_event.type == SDL_KEYUP && !_event.key.repeat)
            SDL_Log("[%s] [KEY UP]   | time %d; char %s; (InputHandler.cpp)", timestr, _event.key.timestamp, SDL_GetKeyName(keyPressed));

        if (_event.type == SDL_QUIT)
            done = true;
    }

    //borderless fullscreen window
    if (!windowBorderless && keystate[SDL_SCANCODE_B]) {
        SDL_SetWindowBordered(window, SDL_FALSE);
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        windowBorderless = true;
    }

    if (windowBorderless && keystate[SDL_SCANCODE_N]) {
        SDL_SetWindowFullscreen(window, 0);
        SDL_SetWindowBordered(window, SDL_TRUE);
        windowBorderless = false;
    }

    //reset acceleration every tick
    player.acceleration = 0;

    //jump
    if (keystate[SDL_SCANCODE_X]) { player.stateMachine.IS_JUMPING = true; player.animationState = 3;}
    else player.stateMachine.IS_JUMPING = false;

    //attack
    if (keystate[SDL_SCANCODE_Z]) { player.stateMachine.IS_ATTACKING = true; player.animationState = 4;}
    else player.stateMachine.IS_ATTACKING = false;

    //handle movement, deal with deceleration where necessary
    if (keystate[SDL_SCANCODE_LEFT]) { player.MoveLeft(); } 
    else if (player.velocity.X < 0) { player.acceleration = 1; }

    if (keystate[SDL_SCANCODE_RIGHT]) { player.MoveRight(); } 
    else if (player.velocity.X > 0) { player.acceleration = (-1); }

    //handle aiming, reset to false if nothing is pressed
    if (keystate[SDL_SCANCODE_UP]) { 
        player.stateMachine.IS_AIMING_UP = true; 
        player.stateMachine.IS_AIMING_DOWN = false;
        player.stateMachine.IS_FACING_RIGHT = false;
        player.stateMachine.IS_FACING_LEFT = false;
    }
    else
        player.stateMachine.IS_AIMING_UP = false;

    if (keystate[SDL_SCANCODE_DOWN]) {  
        player.stateMachine.IS_AIMING_UP = false;
        player.stateMachine.IS_AIMING_DOWN = true;
        player.stateMachine.IS_FACING_RIGHT = false;
        player.stateMachine.IS_FACING_LEFT = false;
    }
    else
        player.stateMachine.IS_AIMING_DOWN = false;

    if (keystate[SDL_SCANCODE_ESCAPE]) done = true; //for now, exit
    if (keystate[SDL_SCANCODE_LSHIFT]);
}