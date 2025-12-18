#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated), sprite(){
    
}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH) : Component(associated), sprite(file, frameCountW, frameCountH){
    associated.box.SetW(sprite.GetWidth());
    associated.box.SetH(sprite.GetHeight());

    SetFrame(0, SDL_FLIP_NONE);
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH){
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::Open(std::string file){
    sprite.Open(file);
    associated.box.SetW(sprite.GetWidth());
    associated.box.SetH(sprite.GetHeight());
    SetFrame(0, SDL_FLIP_NONE);
}

void SpriteRenderer::SetFrame(int frame){
    sprite.SetFrame(frame);
}
void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip){
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}
void SpriteRenderer::SetFlip(SDL_RendererFlip flip){
    sprite.SetFlip(flip);
}

void SpriteRenderer::Start(){
    
}

void SpriteRenderer::Update(float dt){
    
}

void SpriteRenderer::Render(){
    sprite.Render(associated.box.GetX(), associated.box.GetY(), associated.box.GetW(), associated.box.GetH(), associated.angleDeg);
}

void SpriteRenderer::setCameraFollower(bool cameraFollower){
    sprite.cameraFollower = cameraFollower;
}

void SpriteRenderer::SetScale(float scaleX, float scaleY){
    Vec2 oldCenter = associated.box.GetCenter();

    sprite.SetScale(scaleX, scaleY);
    associated.box.SetW(sprite.GetWidth());
    associated.box.SetH(sprite.GetHeight());

    associated.box.SetCenter(oldCenter);
}