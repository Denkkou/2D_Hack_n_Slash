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

    //log initialisation
    SDL_Log("Game World initialised");
}

//implement a timer sync function
void GameWorld::Run() {
    while (!done) {
        //reset timer, begin counting
        timer.resetTicks();

        //receive input and handle
        inputHandler.HandleInput(done, player);   
       
        //update state of the game world
        Update();

        //push changes to renderer
        Render();

        //delay for rest of frame
        if (timer.getTicks() < DELTA_TIME)
            SDL_Delay(DELTA_TIME - timer.getTicks());

    }
}

void GameWorld::Update() {
    //call the update function of all containers
    terrainContainer.Update();
    player.Update();
}

void GameWorld::Render() {
    //clear screen with black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //call the render function of all containers
    terrainContainer.Render(renderer);
    player.Render(renderer);

    //push changes
    SDL_RenderPresent(renderer);
}