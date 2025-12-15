#include "TileSet.h"

#include <stdexcept>

TileSet::TileSet(int tileWidth,
                 int tileHeight,
                 std::string file)
    : tileWidth(tileWidth),
      tileHeight(tileHeight) {
    
    tileSet.Open(file);
    if (!tileSet.IsOpen()) {
        throw std::runtime_error("[TileSet::TileSet] Failed to load tileset texture from file: " + file);
    }
    
    int textureWidth = tileSet.GetWidth();
    int textureHeight = tileSet.GetHeight();

    int lines = textureWidth/tileWidth;
    int columns = textureHeight/tileHeight;

    tileCount = lines * columns;
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index > (tileCount-1) || index < 0){
      throw std::invalid_argument("[TileSet::RenderTile] Index is out of bounds of tileCount");
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