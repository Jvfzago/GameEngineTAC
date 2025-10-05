
#include "state.h"
#include "SpriteRenderer.h"
#include "TileSet.h"
#include "TileMap.h"
#include <algorithm>




State::State() : quitRequested(false){
    GameObject* bg = new GameObject();
    bg->AddComponent(std::unique_ptr<SpriteRenderer>(new SpriteRenderer(*bg, "Recursos/img/Background.png")));
    AddObject(bg);

    GameObject* tileMap = new GameObject();
    TileSet* tileSet = new TileSet(64, 64, "Recursos/img/Tileset.png");
    tileMap->AddComponent(std::unique_ptr<TileMap>(new TileMap(*tileMap, "Recursos/tileMap.txt", tileSet)));
    AddObject(tileMap);
    tileMap->box.SetW(0);
    tileMap->box.SetH(0);


    GameObject* zombie = new GameObject();
    zombie->box.SetX(600);
    zombie->box.SetY(450);
    music = Music("Recursos/audio/BGM.wav");
    music.Play(-1);
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
