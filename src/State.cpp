
#include "State.h"
#include "SpriteRenderer.h"
#include "TileSet.h"
#include "TileMap.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <fstream>    // C++11-friendly file existence check
#include <direct.h>   // _getcwd on Windows
#include <limits.h>   // _MAX_PATH
#include <stdlib.h>

#define PATH_BUFFER_SIZE 260


State::State() : quitRequested(false){
    
    // CWD usando _getcwd (C++11 compatible)
    char cwd[PATH_BUFFER_SIZE];
    if (_getcwd(cwd, PATH_BUFFER_SIZE) != nullptr) {
        std::cout << "[State] Current working directory: " << cwd << std::endl;
    } else {
        std::cout << "[State] Could not get current working directory" << std::endl;
    }

    // Verifica existência do arquivo com std::ifstream (compatível C++11)
    std::ifstream f("Recursos\\audio\\BGM.wav");
    if (!f.is_open()) {
        std::cerr << "[State] Warning: Recursos\\audio\\BGM.wav not found relative to CWD." << std::endl;
    } else {
        std::cout << "[State] Found Recursos\\audio\\BGM.wav" << std::endl;
    }

    try {
        music.Open("Recursos/audio/BGM.wav");
        music.Play(-1);
    } catch (const std::runtime_error& e) {
        printf("Erro ao tocar musica de fundo: %s\n", e.what());
    }
    
    
    GameObject* bg = new GameObject();
    bg->AddComponent(std::unique_ptr<SpriteRenderer>(new SpriteRenderer(*bg, "Recursos/img/Background.png")));
    AddObject(bg);

    GameObject* tileMap = new GameObject();
    TileSet* tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");
    tileMap->AddComponent(std::unique_ptr<TileMap>(new TileMap(*tileMap, "Recursos/map/map.txt", tileSet)));
    AddObject(tileMap);
    tileMap->box.SetW(0);
    tileMap->box.SetH(0);


    GameObject* zombie = new GameObject();
    zombie->box.SetX(600);
    zombie->box.SetY(450);
    printf("State criado\n");
}

State::~State(){
    objectArray.clear();
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::LoadAssets(){
    
}

void State::Update(float dt){
    if(SDL_QuitRequested()){
        quitRequested = true;
    }

    for(auto& go: objectArray){
        go->Update(dt);
    }


    
    
    // for(unsigned int i = 0; i < objectArray.size(); i++){
    //     if(objectArray[i]->IsDead()){
    //         objectArray.erase(objectArray.begin() + i);
    //         i--;
    //     }
    // }

    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(),
            [](std::unique_ptr<GameObject>& go_ptr) { 
                
                bool isDead = go_ptr->IsDead();
                
                return isDead; 
            }),
        objectArray.end());
}

void State::Render(){
    for(auto& go: objectArray){
        go->Render();
    }
}


void State::AddObject(GameObject* go){
    objectArray.emplace_back(go);
}
