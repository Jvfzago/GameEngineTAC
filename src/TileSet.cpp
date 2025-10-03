#include "TileSet.h"

#include <stdexcept>

TileSet::TileSet(int tileWidth,
                 int tileHeight,
                 std::string file)
    : tileWidth(tileWidth),
      tileHeight(tileHeight) {
    // Load the texture from file
    tileSet.Open(file);
    if (!tileSet.IsOpen()) {
        throw std::runtime_error("Failed to load tileset texture from file: " + file);
    }
    // Calculate titleCount based on texture size and tile dimensions
    int textureWidth = tileSet.GetWidth();
    int textureHeight = tileSet.GetHeight();

    int lines = textureWidth/tileWidth;
    int columns = textureHeight/tileHeight;

    tileCount = lines * columns;
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index > (tileCount-1) || index > 0){
      throw std::invalid_argument("Index is out of bounds of tileCount");
    }

    int columns = tileSet.GetWidth() / tileWidth;
    int lines = tileSet.GetHeight() / tileHeight;
    int tileX = (index % columns) * tileWidth;
    int tileY = (index / columns) * tileHeight;

    tileSet.SetClip(tileX, tileY, tileWidth, tileHeight);
    tileSet.Render(static_cast<int>(x), static_cast<int>(y), tileWidth, tileHeight);
}

int TileSet::GetTileWidth() const {
    return tileWidth;
}

int TileSet::GetTileHeight() const {
    return tileHeight;
}