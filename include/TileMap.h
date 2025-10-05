#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <memory>
#include "TileSet.h"
#include "GameObject.h"
#include "Component.h"

class TileMap : public Component {
    private:
        std::vector<int> tileMatrix;
        std::unique_ptr<TileSet> tileSet;

        int mapWidth;
        int mapHeight;
        int mapDepht;
    public:
        TileMap(GameObject& associated, std::string file, TileSet* tileSet);

        void Load(std::string file);
        void SetTileset(TileSet* tileSet);
        int& At(int x, int y, int z = 0);
        void Render() override;
        void RenderLayer(int layer);
        void Update(float dt) override;
        int GetWidth();
        int GetHeight();
        int GetDepth();
};

#endif  // TILEMAP_H