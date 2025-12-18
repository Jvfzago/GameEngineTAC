#include "GameObject.h"

#include <algorithm>

GameObject::GameObject() : isDead(false), components(), started(false), angleDeg(0.0) {
}

GameObject::~GameObject() {
    components.clear();

}

void GameObject::Start(){
    if(!started){
        for(auto& cpt : components){
            cpt->Start();
        }
        started = true;
    }
}

void GameObject::Update(float dt){
    for(auto& cpt : components){
        cpt->Update(dt);
    }
}

void GameObject::Render(){
    for(auto& cpt : components){
        cpt->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(std::unique_ptr<Component>&& cpt){
    if (isDead) return;
    components.push_back(std::move(cpt));
    if (started){
        components.back()->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt) {
    // Usamos remove_if para encontrar o unique_ptr que 'possui' o ponteiro cpt
    components.erase(
        std::remove_if(components.begin(), components.end(),
                       // Lambda que retorna true se o ponteiro crú for igual a cpt
                       [cpt](const std::unique_ptr<Component>& component_ptr) {
                           return component_ptr.get() == cpt;
                       }),
        components.end()
    );
}