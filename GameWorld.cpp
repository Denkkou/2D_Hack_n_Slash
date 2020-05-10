#include "GameWorld.h"

GameWorld::GameWorld() {
    SDL_Log("GameWorld created");
}

GameWorld::~GameWorld() {
    SDL_Log("GameWorld destroyed");
}

void GameWorld::Init() {
    //create window and renderer
    window = SDL_CreateWindow("[Joe Schofield - SCH18683720] CGP2015M - 2D Hack 'n' Slash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    player.playerSprite.Load(renderer, "content/sprites/player_sheet.png", false);
    SDL_Log("Player sprite loaded");

    //log initialisation
    SDL_Log("Game World initialised");
}

//implement a timer sync function
void GameWorld::Run() {
    while (!done) {
        //reset timer, begin counting
        timer.resetTicks();

        //receive input and handle
        inputHandler.HandleInput(done, player, timeGetter, window);   
       
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
    player.Update(timeGetter);

    //reset grounding
    player.stateMachine.IS_GROUNDED = false;

    //detect for collision of platform terrain
    for (int i = 0; i < terrainContainer.aListOfPlatformObjects.size(); i++) {
        if (detectedCollision(player, terrainContainer.aListOfPlatformObjects[i])) {
            //move player up to object's y
            player.MoveUpOnCollision(terrainContainer.aListOfPlatformObjects[i]->Y);
        }
    }

    //detect for collision of pillar terrain
    for (int i = 0; i < terrainContainer.aListOfPillarObjects.size(); i++) {
        //if colliding from the sides
        if (detectedCollision(player, terrainContainer.aListOfPillarObjects[i])) {
            //reposition player, cancel their velocity
            player.MoveSidewaysOnCollision(terrainContainer.aListOfPillarObjects[i]->X, terrainContainer.aListOfPillarObjects[i]->W);
        }
    }
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

bool GameWorld::detectedCollision(Player &player, TerrainObject* object) {
    //detect collision
    if (player.posX  < object->X + object->W &&
        player.posX + player.width > object->X &&
        player.posY + (player.height - object->H) < object->Y &&
        player.posY + (player.height + player.feetBoxOffset) > object->Y) {
        return true;
    }
    return false;
}

