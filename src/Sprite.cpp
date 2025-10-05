#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite() : texture(nullptr){
    
}

Sprite::Sprite(string file, int frameCountW, int frameCountH) : 
frameCountW(frameCountW), frameCountH(frameCountH), texture(nullptr){
    Open(file);
}

Sprite::~Sprite(){
    texture = nullptr;
}

void Sprite::Open(string file){

    texture = Resources::GetImage(file);
    if(texture == nullptr){
        throw string("Deu o seguinte erro ao carregar a textura: ") + SDL_GetError();
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
        throw string("Não tem textura pra renderizar");
    }
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
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
        throw string("Frame inválido");
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
