#include "InputHander.h"

//needs SDL quit code and a way of handling escape
void InputHandler::HandleInput(bool& done, GameActor& player) {
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT)
            done = true;
    }

    //reset acceleration every tick
    player.acceleration = 0;

    if (keystate[SDL_SCANCODE_X]) player.stateMachine.IS_JUMPING = true;
    else player.stateMachine.IS_JUMPING = false;

    if (keystate[SDL_SCANCODE_Z]) player.stateMachine.IS_ATTACKING = true;
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