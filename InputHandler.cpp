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

        //get time and store
        SDL_Keycode keyPressed = _event.key.keysym.sym;
        char timestr[32];
        getTime(timestr, 32);

        if (_event.type == SDL_KEYDOWN && !_event.key.repeat) {
            SDL_Log("[%s] [KEY DOWN] time %d; code %d; char %s;", timestr, _event.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
            switch (_event.key.keysym.sym) {
            case SDLK_x:
                return buttonX_;
                break;
            case SDLK_z:
                return buttonZ_;
                break;
            case SDLK_LEFT:
                return buttonLeft_;
                break;
            case SDLK_RIGHT:
                return buttonRight_;
                break;
            case SDLK_ESCAPE:
                return buttonEscape_;
                break;
            case SDLK_LSHIFT:
                return buttonLShift_;
                break;
            }
        }
    }
    //if nothing is pressed, do nothing
    return DoNothing;
}

//get formatted current time when called
bool InputHandler::getTime(char* buffer, int bufferSize) {
    //get current time
    time_t currentTime = std::time(0);
    struct tm info;
    localtime_s(&info, &currentTime);

    //format time to readable
    size_t written = strftime(buffer, bufferSize, "%d/%m/%y %T", &info);

    return written != 0;
}