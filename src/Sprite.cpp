#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite() : texture(nullptr), 
clipRect({}),
width(0), height(0),
frameCountW(1), frameCountH(1), cameraFollower(false), flip(SDL_FLIP_NONE), scale(1.0f, 1.0f) {
    
}

Sprite::Sprite(string file, int frameCountW, int frameCountH) : Sprite() {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    Open(file);
}

Sprite::~Sprite(){
    texture = nullptr;
}

void Sprite::Open(string file){

    texture = Resources::GetImage(file);
    if(texture == nullptr){
        throw string("[Sprite::Open] Deu o seguinte erro ao carregar a textura: ") + SDL_GetError();
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0,0,width,height);
}

void Sprite::SetClip(int x, int y, int w,int h){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y, int w, int h, double angle){
    if(texture == nullptr){
        throw string("[Sprite::Render] Não tem textura pra renderizar.");
    }
    SDL_Rect dst;
    if (!cameraFollower) {
        dst.x = x - static_cast<int>(Camera::pos.GetX());
        dst.y = y - static_cast<int>(Camera::pos.GetY());
    } else {
        dst.x = x;
        dst.y = y;
    }

    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst);
}

int Sprite::GetWidth(){
    return (width / frameCountW) * scale.GetX();
}

int Sprite::GetHeight(){
    return (height / frameCountH) * scale.GetY();
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}

void Sprite::SetFrame(int frame){
    if(frame < 0 || frame >= frameCountW * frameCountH){
        throw string("[Sprite::SetFrame] Frame inválido.");
    }
    int frameW = width / frameCountW;
    int frameH = height / frameCountH;
    int x = (frame % frameCountW) * frameW;
    int y = (frame / frameCountW) * frameH;
    SetClip(x, y, frameW, frameH);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH){
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
}

void Sprite::SetScale(float scaleX, float scaleY){
    //Se o valor passado apara qualquer escala for 0, mantém o valor atual
    if (scaleX < 0 || scaleY < 0) {
        throw string("[Sprite::SetScale] Scale não pode ser negativo.");
    }
    if (scaleX != 0) {
        scale.SetX(scaleX);
    }
    if (scaleY != 0) {
        scale.SetY(scaleY);
    }
}

Vec2 Sprite::GetScale(){
    return scale;
}

void Sprite::SetFlip(SDL_RendererFlip flip){
    this->flip = flip;
}