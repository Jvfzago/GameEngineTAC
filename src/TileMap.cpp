#include "TileMap.h"

#include <fstream>
#include <stdexcept>
TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet)
     : Component(associated), 
     tileMatrix(),
     tileSet(tileSet), 
     mapWidth(0),
     mapHeight(0),
     mapDepth(0) {
    Load(file);
}

void TileMap::Load(std::string file) {
    std::ifstream infile(file);
    if (!infile.is_open()) {
        throw std::runtime_error("[TileMap::Load] Failed to open tilemap file: " + file);
    }

    char comma; //Variável temporária para ler as vírgulas do arquivo

    infile >> mapWidth >> comma;
    infile >> mapHeight >> comma;
    infile >> mapDepth >> comma;

    tileMatrix.resize(mapWidth * mapHeight * mapDepth);

    for (int z = 0; z < mapDepth; ++z) {
        for (int y = 0; y < mapHeight; ++y) {
            for (int x = 0; x < mapWidth; ++x) {
                int index;
                if (!(infile >> index)) {
                    throw std::runtime_error("[TileMap::Load] Error reading tile index from file: " + file);
                }
                tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight] = index;
                infile >> comma; //Lê a vírgula após o número
            }
        }
    }

    infile.close();
}

void TileMap::SetTileset(TileSet* tileSet) {
    this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight || z < 0 || z >= mapDepth) {
        throw std::out_of_range("[TileMap::At] Indices out of range");
    }
    return tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight];
}

void TileMap::RenderLayer(int layer) {
    if (!tileSet) {
        throw std::runtime_error("[TileMap::RenderLayer] TileSet not set");
    }
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int tileIndex = At(x, y, layer);
            if (tileIndex >= 0) { // -1 indicates no tile
                tileSet->RenderTile(tileIndex, x * tileSet->GetTileWidth(), y * tileSet->GetTileHeight());
            }
        }
    }
}

void TileMap::Render() {
    for (int z = 0; z < mapDepth; ++z) {
        RenderLayer(z);
    }
}

void TileMap::Update(float dt) {
    // Só para o compilador não reclamar
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}