#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated), sprite(){
    
}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH) : Component(associated), sprite(file, frameCountW, frameCountH){
    associated.box.SetW(sprite.GetWidth());
    associated.box.SetH(sprite.GetHeight());

    SetFrame(0);
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH){
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::Open(std::string file){
    sprite.Open(file);
    associated.box.SetW(sprite.GetWidth());
    associated.box.SetH(sprite.GetHeight());
    SetFrame(0);
}

void SpriteRenderer::SetFrame(int frame){
    sprite.SetFrame(frame);
}

void SpriteRenderer::Update(float dt){
    
}

void SpriteRenderer::Render(){
    sprite.Render(associated.box.GetX(), associated.box.GetY(), associated.box.GetW(), associated.box.GetH());
}

void SpriteRenderer::setCameraFollower(bool cameraFollower){
    sprite.cameraFollower = cameraFollower;
}