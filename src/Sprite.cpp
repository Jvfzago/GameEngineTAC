#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite() : texture(nullptr), 
clipRect({}),
width(0), height(0),
frameCountW(1), frameCountH(1), cameraFollwer(false) {
    
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

void Sprite::Render(int x, int y, int w, int h){
    if(texture == nullptr){
        throw string("[Sprite::Render] Não tem textura pra renderizar.");
    }
    SDL_Rect dst;
    dst.x = x - (int)Camera::pos.GetX();
    dst.y = y - (int)Camera::pos.GetY();
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst);
}

int Sprite::GetWidth(){
    return width / frameCountW;
}

int Sprite::GetHeight(){
    return height / frameCountH;
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
