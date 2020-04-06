#include "GameWorld.h"

GameWorld::GameWorld() {
    SDL_Log("GameWorld created");
}

GameWorld::~GameWorld() {
    SDL_Log("GameWorld destroyed");
}

void GameWorld::Init() {
    //create window and renderer
    window = SDL_CreateWindow("SCH18683720 - Game Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //bind commands in input handler
    inputHandler.bindCommands();

    //log initialisation
    SDL_Log("Game World initialised");
}

//implement a timer sync function
void GameWorld::Run() {
    while (!done) {
        //actor still needs to be built
        //it needs to be the basic engine behind
        //a player or npc -> implement movement and
        //the relevant commands

        //receive input and handle
        std::function<void(GameActor&)> command = inputHandler.handleInput();   

        //execute command on player
        command(player);
       
        //update state of the game world
        Update();

        //push changes to renderer
        Render();
    }
}

void GameWorld::Update() {

}

void GameWorld::Render() {
    //clear screen with black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //call the render function of all containers

    //push changes
    SDL_RenderPresent(renderer);
}