#include "InputHander.h"

//define the commands
void DoNothing(GameActor& actor){ /*nothing*/ }
void JumpCommand(GameActor& actor) { actor.Jump(); }
void AttackCommand(GameActor& actor) { actor.Attack(); }
void MoveLeftCommand(GameActor& actor) { actor.MoveLeft(); }
void MoveRightCommand(GameActor& actor) { actor.MoveRight(); }
void EscapeCommand(GameActor& actor) {}
void LShiftCommand(GameActor& actor) {}

//bind commands to buttons
void InputHandler::bindCommands() {
    buttonX_ = JumpCommand;
    buttonZ_ = AttackCommand;
    buttonLeft_ = MoveLeftCommand;
    buttonRight_ = MoveRightCommand;
    buttonEscape_ = EscapeCommand;
    buttonLShift_ = LShiftCommand;
}

//needs SDL quit code and a way of handling escape
std::function<void(GameActor&)> InputHandler::handleInput() {
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_KEYDOWN && !_event.key.repeat) {
            switch (_event.key.keysym.sym) {
            case SDLK_x:
                SDL_Log("X Key Pressed");
                return buttonX_;
                break;
            case SDLK_z:
                SDL_Log("Z Key Pressed");
                return buttonZ_;
                break;
            case SDLK_LEFT:
                SDL_Log("Left Pressed");
                return buttonLeft_;
                break;
            case SDLK_RIGHT:
                SDL_Log("Right Pressed");
                return buttonRight_;
                break;
            case SDLK_ESCAPE:
                SDL_Log("Escape Pressed");
                return buttonEscape_;
                break;
            case SDLK_LSHIFT:
                SDL_Log("LShift Pressed");
                return buttonLShift_;
                break;
            }
        }
    }
    //if nothing is pressed, do nothing
    return DoNothing;
}