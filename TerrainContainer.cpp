#include "TerrainContainer.h"

TerrainContainer::TerrainContainer() {
    SDL_Log("Terrain Container Created");
    //create the level pieces in here

}

TerrainContainer::~TerrainContainer() {
    for (auto& element : aListOfTerrainObjects) {
        delete element;
    }
    SDL_Log("Terrain Container Destroyed");
}

void TerrainContainer::AddObject(int posX, int posY, int width, int height) {
    TerrainObject* aTerrainPiece = new TerrainObject();

    aTerrainPiece->blockPosX = posX;
    aTerrainPiece->blockPosY = posY;
    aTerrainPiece->blockHeight = height;
    aTerrainPiece->blockWidth = width;

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

