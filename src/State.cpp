
#include "State.h"
#include "SpriteRenderer.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Zombie.h"
#include "InputManager.h"
#include "Camera.h"
#include "Character.h"
#include "PlayerController.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <direct.h> 
#include <limits.h>
#include <stdlib.h>

#define PATH_BUFFER_SIZE 260


State::State() : quitRequested(false), started(false) {
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
    bg->GetComponent<SpriteRenderer>()->setCameraFollower(true);
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
    GameObject* character = new GameObject();
    character->box.SetX(1280);
    character->box.SetY(1280);
    Character* characterPtr = new Character(*character, "Recursos/img/Player.png");
    character->AddComponent(std::unique_ptr<Character>(characterPtr));
    std::weak_ptr<GameObject> weak_character = AddObject(character);
    Character::player = characterPtr;

    Camera::Follow(character);

    PlayerController* pc = new PlayerController(*character);
    character->AddComponent(std::unique_ptr<PlayerController>(pc));


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

void State::Start(){
    LoadAssets();
    if(!started){
        for(auto& go: objectArray){
            go->Start();
        }
        started = true;
    }
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

    //Atualiza a câmera
    Camera::Update(dt);

    //-----------------------------------------------------
    if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
        GameObject* zombie = new GameObject();
        zombie->box.SetX(InputManager::GetInstance().GetMouseX() + Camera::pos.GetX());
        zombie->box.SetY(InputManager::GetInstance().GetMouseY() + Camera::pos.GetY());
        zombie->AddComponent(std::unique_ptr<Zombie>(new Zombie(*zombie)));
        AddObject(zombie);
    }




    //-----------------------------------------------------


    //Remove os GameObjects "mortos"
    objectArray.erase(
        std::remove_if(objectArray.begin(), objectArray.end(),
            [](std::shared_ptr<GameObject>& go_ptr) { 
                bool isDead = go_ptr->IsDead();
                
                if (isDead && Camera::GetFocus() == go_ptr.get()) {
                Camera::Unfollow();
                }

                return isDead; 
            }),
        objectArray.end());
}

void State::Render(){
    for(auto& go: objectArray){
        go->Render();
    }
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
    std::shared_ptr<GameObject> go_shared_ptr(go);
    objectArray.push_back(go_shared_ptr);
    if(started){
        go_shared_ptr->Start();
    }
    return std::weak_ptr<GameObject>(go_shared_ptr);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
    // Essa função é geralmente usada para se obter o weak_ptr
    // de algum objeto que já temos o ponteiro puro dele e
    // que já foi adicionado ao vetor de objetos.
    for(auto& obj_ptr: objectArray){
        if(obj_ptr.get() == go){
            return std::weak_ptr<GameObject>(obj_ptr);
        }
    }
    return std::weak_ptr<GameObject>();
}
