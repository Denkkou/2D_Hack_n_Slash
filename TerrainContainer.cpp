#include "TerrainContainer.h"

/*
NOTE ABOUT PILLARS:
    Pillars must always be topped with platforms, or be used as walls only
    The tops of pillars do not function as platforms, they only implement
    X-direction repulsion correctly

    Consider changing the collision code to see if entering from the top or
    from the bottom, then applying appropriate movement
*/

TerrainContainer::TerrainContainer() {
    SDL_Log("Terrain Container Created");
    BuildLevel();
}

TerrainContainer::~TerrainContainer() {
    //clear memory
    for (auto& element : aListOfPlatformObjects) {
        delete element;
    }

    for (auto& element : aListOfPillarObjects) {
        delete element;
    }

    SDL_Log("Terrain Container Destroyed");
}

//create the level pieces in here (tunnelling occurs <10 width)
void TerrainContainer::BuildLevel() {
    AddPlatform(0, 850, 1600, 50); //floor
    AddPlatform(500, 700, 300, 50);
    AddPlatform(800, 650, 300, 50);

    AddPillar(-15, 0, 20, 900); //left wall
    AddPillar(1595, 0, 20, 900); //right wall
}

//create a platform the player can jump up through
void TerrainContainer::AddPlatform(int posX, int posY, int width, int height) {
    TerrainObject* aTerrainPiece = new Platform(posX, posY, width, height);
    this->aListOfPlatformObjects.push_back(aTerrainPiece);
}

//create a pillar with horizontal collision
void TerrainContainer::AddPillar(int posX, int posY, int width, int height) {
    TerrainObject* aTerrainPiece = new Pillar(posX, posY, width, height);
    this->aListOfPillarObjects.push_back(aTerrainPiece);
}

void TerrainContainer::Update() {
    //update all platforms
    for (auto& element : aListOfPlatformObjects) {
        element->Update();
    }

    //update all pillars
    for (auto& element : aListOfPillarObjects) {
        element->Update();
    }
}

void TerrainContainer::Render(SDL_Renderer* aRenderer) {
    //render all platforms
    for (auto& element : aListOfPlatformObjects) {
        element->Render(aRenderer);
    }

    //render all pillars
    for (auto& element : aListOfPillarObjects) {
        element->Render(aRenderer);
    }
}

