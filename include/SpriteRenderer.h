#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.h"
#include "Sprite.h"
#include "GameObject.h"


class SpriteRenderer : public Component {
   private:
    Sprite sprite;
   public:
    SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);
    void Open(std::string file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void SetFrame(int frame);
    void SetFrame(int frame, SDL_RendererFlip flip);

    void setCameraFollower(bool cameraFollower);

    void SetScale(float scaleX, float scaleY);
};

#endif  // SPRITERENDERER_H