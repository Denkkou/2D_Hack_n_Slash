#include "TerrainContainer.h"

TerrainContainer::TerrainContainer() {
    SDL_Log("Terrain Container Created");

    //create the level pieces in here
    AddObject(0, 850, 1600, 50); //base
    AddObject(500, 700, 300, 50);
    AddObject(800, 650, 300, 50);
}

TerrainContainer::~TerrainContainer() {
    for (auto& element : aListOfTerrainObjects) {
        delete element;
    }
    SDL_Log("Terrain Container Destroyed");
}

void TerrainContainer::AddObject(int posX, int posY, int width, int height) {
    TerrainObject* aTerrainPiece = new TerrainObject(posX, posY, width, height);
    this->aListOfTerrainObjects.push_back(aTerrainPiece);
}

void TerrainContainer::Update() {
    for (auto& element : aListOfTerrainObjects) {
        element->Update();
    }
}

void TerrainContainer::Render(SDL_Renderer* aRenderer) {
    for (auto& element : aListOfTerrainObjects) {
        element->Render(aRenderer);
    }
}

