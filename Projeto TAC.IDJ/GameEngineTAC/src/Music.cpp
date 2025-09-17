#include  "Music.h"

Music::Music() {
    music = nullptr;
}

Music::Music(string file) {
    music = nullptr;
    Open(file);
}

void Music::Play(int times = -1) {
    if(music == nullptr){
        throw string("Nao tem musica pra tocar");
    }
    Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop = 1500) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    if(music != nullptr){
        Mix_FreeMusic(music);
    }
    music = Mix_LoadMUS(file.c_str());
    if(music == nullptr){
        throw string("Deu o seguinte erro ao carregar a musica: ") + SDL_GetError();
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}

Music::~Music() {
    Stop();
    if(music != nullptr){
        Mix_FreeMusic(music);
    }
}