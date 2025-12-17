#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "InputManager.h"


Zombie::Zombie(GameObject& associated) : Component(associated), hitpoints(100), deathSound("Recursos/audio/Dead.wav"), hitSound("Recursos/audio/Hit0.wav") {
    SpriteRenderer* spriteR = new SpriteRenderer(associated, "Recursos/img/Enemy.png", 3, 2);
    associated.AddComponent(std::unique_ptr<SpriteRenderer>(spriteR));
    
    Animator* animator = new Animator(associated);
    associated.AddComponent(std::unique_ptr<Animator>(animator));
    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->SetAnimation("walking");
}

void Zombie::Damage(int damage) {
    Animator* animator = associated.GetComponent<Animator>();
    hitpoints -= damage;
    hitSound.Play(1);


    if (hitpoints <= 0 ) {
        hitpoints = 0;
        animator->SetAnimation("dead");
        deathSound.Play(1);
    }
}

void Zombie::Update(float dt) {
    if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)) {
        if( InputManager::GetInstance().GetMouseX() >= associated.box.GetX() &&
            InputManager::GetInstance().GetMouseX() <= associated.box.GetX() + associated.box.GetW() &&
            InputManager::GetInstance().GetMouseY() >= associated.box.GetY() &&
            InputManager::GetInstance().GetMouseY() <= associated.box.GetY() + associated.box.GetH()
        ) {
            Damage(20);
        }
    }
}

void Zombie::Render() {
    
}