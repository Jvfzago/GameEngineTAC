#include "Game.h"
#include "Resources.h"
#include <stdexcept>
#include <cstdio>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <iostream>

Game* Game::instance = nullptr;

Game& Game::GetInstance(){
     if(instance == nullptr){
         instance = new Game("242039256 - Joao Vitor Frabis Zago", 1200, 900);
     }
     return *instance;
 }

Game::Game(string title, int width, int height) : window(nullptr), renderer(nullptr), state(nullptr) {
    if(instance != nullptr){
        throw string("Já tem uma instância de Game");
    } else {
        instance = this;
    }

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        throw string("Deu o seguinte erro ao inicializar o SDL: ") + SDL_GetError();
    }
    else {
        std::cout << "[Game] SDL initialized successfully." << std::endl;
    }

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0){
        throw string("Deu o seguinte erro ao inicializar o SDL_image: ") + SDL_GetError();
    }
    else {
        std::cout << "[Game] SDL_image initialized successfully." << std::endl;
    }

    // 1. Tente inicializar as flags OGG
    int mixFlags = MIX_INIT_OGG;
    int initResult = Mix_Init(mixFlags);

    // 2. Verifique se todas as flags solicitadas foram realmente inicializadas.
    // Se o resultado E (AND) as flags for DIFERENTE das flags, significa falha parcial.
    if ((initResult & mixFlags) != mixFlags) {
        // Isso garante que se a libogg.dll falhar, a exceção é lançada.
        throw std::runtime_error("Erro ao inicializar o SDL_mixer (Faltando codec OGG?): " + std::string(Mix_GetError()));
    }
    else {
        std::cout << "[Game] SDL_mixer initialized successfully with OGG support." << std::endl;
    }
    
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0){
        throw string("Deu o seguinte erro ao abrir o áudio: ") + SDL_GetError();
    }
    else {
        std::cout << "[Game] Audio device opened successfully." << std::endl;
    }
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == nullptr){
        throw string("Deu o seguinte erro ao criar a janela: ") + SDL_GetError();
    }
    else {
        std::cout << "[Game] Window created successfully." << std::endl;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        throw string("Deu o seguinte erro ao criar o renderizador: ") + SDL_GetError();
    }
    else {
        std::cout << "[Game] Renderer created successfully." << std::endl;
    }

    state = new State();
    
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
    int frameCount = 0;

    if (state == nullptr) {
        // Se o State não foi inicializado, jogue um erro claro para o debugger
        throw std::runtime_error("Erro FATAL: O objeto State (state) é nulo!");
    }

    while(!state->QuitRequested()){


        state->Update(0);

        frameCount++;
        fprintf(stderr, "Frame: %d", frameCount);

        
        SDL_RenderClear(renderer);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);

    }

    std::cout << "[Game] Game loop has ended. Cleaning up resources." << std::endl;
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}