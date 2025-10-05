#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"


Zombie::Zombie(GameObject& associated) : Component(associated), hitpoints(100) {
    SpriteRenderer* spriteR = new SpriteRenderer(associated, "Recursos/img/Enemy.png", 3, 2);
    associated.AddComponent(std::unique_ptr<SpriteRenderer>(spriteR));
    
    Animator* animator = new Animator(associated);
    associated.AddComponent(std::unique_ptr<Animator>(animator));
    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));
    animator->SetAnimation("walking");

    deathSound = new Sound("Recursos/audio/Dead.wav");
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        hitpoints = 0;
        deathSound->Play(1);
        associated.GetComponent<SpriteRenderer>()->SetFrame(5); // Morto
    }
}

void Zombie::Update(float dt) {
    Damage(1);
}

void Zombie::Render() {
    
}