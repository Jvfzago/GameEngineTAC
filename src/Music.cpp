#include  "Music.h"
#include <stdexcept>
#include <Resources.h>

Music::Music(): music(nullptr) {}

Music::Music(string file): Music() {
    Open(file);
}

void Music::Play(int times) {

    if (Mix_QuerySpec(nullptr, nullptr, nullptr) == 0) {
        // Se a SDL_mixer não estiver aberta, lance um erro (ou não faça nada).
        throw std::runtime_error("[Music/Play] SDL_mixer não está inicializado. (Mix_OpenAudio não foi chamado com sucesso.)");
        // Se este for o caso, a SDL_mixer está falhando no Game::Game.
        return; 
    }

    if (music == nullptr) {
        throw std::runtime_error("[Music::Play] Não ha musica para tocar: Ponteiro nulo.");
    }
    if (Mix_PlayMusic(music, times) == -1) {
        throw std::runtime_error("[Music::Play] Erro ao tocar musica: " + std::string(SDL_GetError()));
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    if(music != nullptr){
        Mix_FreeMusic(music);
    }
    music = Resources::GetMusic(file);
    if(music == nullptr){
        throw std::runtime_error(std::string("[Music::Open] Deu o seguinte erro ao carregar a musica: ") + SDL_GetError());
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