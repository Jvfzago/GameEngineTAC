
#include "State.h"
#include "SpriteRenderer.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Zombie.h"
#include "InputManager.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <direct.h> 
#include <limits.h>
#include <stdlib.h>

#define PATH_BUFFER_SIZE 260


State::State() : quitRequested(false){
    std::cout << "[State::State] Initializing State..." << std::endl;

    try {
        music.Open("Recursos/audio/BGM.wav");
        music.Play(-1);
    } catch (const std::runtime_error& e) {
        printf("[State::State] Erro ao tocar musica de fundo: %s\n", e.what());
    }
    
    std::cout << "[State::State] Music played successfully." << std::endl;
    
    GameObject* bg = new GameObject();
    bg->AddComponent(std::unique_ptr<SpriteRenderer>(new SpriteRenderer(*bg, "Recursos/img/Background.png")));
    AddObject(bg);

    std::cout << "[State::State] Background loaded successfully." << std::endl;

    GameObject* tileMap = new GameObject();
    TileSet* tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");
    tileMap->AddComponent(std::unique_ptr<TileMap>(new TileMap(*tileMap, "Recursos/map/map.txt", tileSet)));
    AddObject(tileMap);
    tileMap->box.SetW(0);
    tileMap->box.SetH(0);

    std::cout << "[State::State] TileMap loaded successfully." << std::endl;

    //-----------------------------------------------------------------------


    //-----------------------------------------------------------------------

    std::cout << "[State::State] State initialized successfully." << std::endl;
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
    //Verifica se o usuário pediu para sair
    if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE) || InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }

    //Atualiza todos os GameObjects
    for (size_t i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Update(dt);
}
    //-----------------------------------------------------
    if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
        GameObject* zombie = new GameObject();
        zombie->box.SetX(InputManager::GetInstance().GetMouseX());
        zombie->box.SetY(InputManager::GetInstance().GetMouseY());
        zombie->AddComponent(std::unique_ptr<Zombie>(new Zombie(*zombie)));
        AddObject(zombie);
    }




    //-----------------------------------------------------


    //Remove os GameObjects "mortos"
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
