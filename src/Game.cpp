 
#include "Game.h"

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance(){
     if(instance == nullptr){
         instance = new Game("242039256 - Joao Vitor Frabis Zago", 1200, 900);
     }
     return *instance;
 }

Game::Game(string title, int width, int height){
    if(instance != nullptr){
        throw string("Já tem uma instância de Game");
    } else {
        instance = this;
    }

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        throw string("Deu o seguinte erro ao inicializar o SDL: ") + SDL_GetError();
    }

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0){
        throw string("Deu o seguinte erro ao inicializar o SDL_image: ") + SDL_GetError();
    }

    if(Mix_Init(MIX_INIT_OGG) == 0){
        throw string("Deu o seguinte erro ao inicializar o SDL_mixer: ") + SDL_GetError();
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0){
        throw string("Deu o seguinte erro ao fazer open audio: ") + SDL_GetError();
    }
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == nullptr){
        throw string("Deu o seguinte erro ao criar a janela: ") + SDL_GetError();
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        throw string("Deu o seguinte erro ao criar o renderizador: ") + SDL_GetError();
    }

}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

State& Game::GetState(){
    return *state;
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

void Game::Run(){
    while(!state->QuitRequested()){
        state->Update(0);
        SDL_RenderClear(renderer);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);

    }
}