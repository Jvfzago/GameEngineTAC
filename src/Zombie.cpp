#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "InputManager.h"
#include "Camera.h"



Zombie::Zombie(GameObject& associated) : 
    Component(associated), 
    hitpoints(100), 
    deathSound("Recursos/audio/Dead.wav"), 
    hitSound("Recursos/audio/Hit0.wav"), 
    hit(false),
    hitTimer(),
    deathTimer()
    {
    SpriteRenderer* spriteR = new SpriteRenderer(associated, "Recursos/img/Enemy.png", 3, 2);
    associated.AddComponent(std::unique_ptr<SpriteRenderer>(spriteR));
    
    Animator* animator = new Animator(associated);
    associated.AddComponent(std::unique_ptr<Animator>(animator));
    animator->AddAnimation("walking", Animation(0, 3, 0.5f));
    animator->AddAnimation("dead", Animation(5, 5, 0.0f));
    animator->AddAnimation("hit", Animation(4, 4, 0.0f));
    animator->SetAnimation("walking");
}

void Zombie::Damage(int damage) {
    Animator* animator = associated.GetComponent<Animator>();
    if (!animator) return;
    hitpoints -= damage;
    hitSound.Play(1);


    if (hitpoints <= 0 ) {
        hitpoints = 0;
        animator->SetAnimation("dead");
        deathSound.Play(1);
    } else {
        hit = true;
        hitTimer.Restart();
        animator->SetAnimation("hit");
    }
}

void Zombie::Update(float dt) {
    if (associated.IsDead()) return;
    hitTimer.Update(dt);

    if( hitpoints <= 0 ) {
        deathTimer.Update(dt);
        if(deathTimer.Get() > 5.0f) {
            deathTimer.Restart();
            associated.RequestDelete();
            return;
        }
    } else {
        float mouseWorldX = InputManager::GetInstance().GetMouseX() + Camera::pos.GetX();
        float mouseWorldY = InputManager::GetInstance().GetMouseY() + Camera::pos.GetY();

        if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)) {
            if( mouseWorldX >= associated.box.GetX() &&
                mouseWorldX <= associated.box.GetX() + associated.box.GetW() &&
                mouseWorldY >= associated.box.GetY() &&
                mouseWorldY <= associated.box.GetY() + associated.box.GetH()
            ) {
                Damage(20);
            }
        }

        if(hit == true && hitpoints != 0 && hitTimer.Get() > 0.5f) {
            Animator* animator = associated.GetComponent<Animator>();

            animator->SetAnimation("walking");
            hit = false;
        }
    }

    
    

}

void Zombie::Render() {
    
}