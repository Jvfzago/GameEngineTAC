#include "TileMap.h"

#include <fstream>
#include <stdexcept>
TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet)  : tileSet(tileSet) {
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