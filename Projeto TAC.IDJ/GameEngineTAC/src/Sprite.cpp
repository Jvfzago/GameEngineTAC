#include "Sprite.h"
#include "Game.h"
Sprite::Sprite(){
    texture = nullptr;
}

Sprite::Sprite(string file){
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(string file){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
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

void Sprite::Render(int x, int y){
    if(texture == nullptr){
        throw string("Não tem textura pra renderizar");
    }
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = clipRect.w;
    dst.h = clipRect.h;
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst);
}

int Sprite::GetWidth(){
    return width;
}

int Sprite::GetHeight(){
    return height;
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}