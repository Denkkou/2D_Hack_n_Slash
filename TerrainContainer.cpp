#include "TerrainContainer.h"

TerrainContainer::TerrainContainer() {
    SDL_Log("Terrain Container Created");

    //create the level pieces in here
    AddPlatform(0, 850, 1600, 50); //base
    AddPlatform(500, 700, 300, 50);
    AddPlatform(800, 650, 300, 50);

    AddPillar(0, 0, 20, 900); //left wall
    AddPillar(1580, 0, 20, 900); //right wall
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

//create a platform the player can jump up through
void TerrainContainer::AddPlatform(int posX, int posY, int width, int height) {
    TerrainObject* aTerrainPiece = new Platform(posX, posY, width, height);
    this->aListOfPlatformObjects.push_back(aTerrainPiece);
}

//create a pillar with total collision
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

