#include "InputHander.h"

//define the commands
void DoNothing(GameActor& actor) { actor.DoNothing(); }
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
std::function<void(GameActor&)> InputHandler::handleInput(bool& done) {
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT)
            done = true;
    }

    if (keystate[SDL_SCANCODE_X]) return buttonX_;
    if (keystate[SDL_SCANCODE_Z]) return buttonZ_;
    if (keystate[SDL_SCANCODE_LEFT]) return buttonLeft_;
    if (keystate[SDL_SCANCODE_RIGHT]) return buttonRight_;
    if (keystate[SDL_SCANCODE_ESCAPE]) return buttonEscape_;
    if (keystate[SDL_SCANCODE_LSHIFT]) return buttonLShift_;
    
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