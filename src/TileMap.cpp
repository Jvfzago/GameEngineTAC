#include "TileMap.h"

#include <fstream>
#include <stdexcept>
TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet)  : Component(associated), tileSet(tileSet) {
    Load(file);
}

void TileMap::Load(std::string file) {
    std::ifstream infile(file);
    if (!infile.is_open()) {
        throw std::runtime_error("Failed to open tilemap file: " + file);
    }

    infile >> mapWidth >> mapHeight >> mapDepht;

    tileMatrix.resize(mapWidth * mapHeight * mapDepht);

    for (int z = 0; z < mapDepht; ++z) {
        for (int y = 0; y < mapHeight; ++y) {
            for (int x = 0; x < mapWidth; ++x) {
                int index;
                infile >> index;
                tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight] = index;
            }
        }
    }

    infile.close();
}

void TileMap::SetTileset(TileSet* tileSet) {
    this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight || z < 0 || z >= mapDepht) {
        throw std::out_of_range("TileMap::At - Indices out of range");
    }
    return tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight];
}

void TileMap::RenderLayer(int layer) {
    if (!tileSet) {
        throw std::runtime_error("TileMap::RenderLayer - TileSet not set");
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
    for (int z = 0; z < mapDepht; ++z) {
        RenderLayer(z);
    }
}

void TileMap::Update(float dt) {
    // Só para o compliador não reclamar
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepht;
}