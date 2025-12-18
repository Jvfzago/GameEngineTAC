#include "Character.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Gun.h"
#include "Game.h"

#include <iostream>

Character* Character::player = nullptr;

Character::Character(GameObject& associated, std::string sprite) 
    : Component(associated),
      gun(),
      speed(0, 0),
      linearSpeed(0),
      hp(100),
      deathTimer()
{
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, sprite, 3, 4);
    associated.AddComponent(std::unique_ptr<SpriteRenderer>(spriteRenderer));

    Animator* animator = new Animator(associated);
    associated.AddComponent(std::unique_ptr<Animator>(animator));

    animator->AddAnimation("idle", Animation(6, 9, 0.25f));
    animator->AddAnimation("walking", Animation(0, 5, 0.25f));
    animator->AddAnimation("dead", Animation(10, 11, 0.5f));

    animator->SetAnimation("idle");
}

Character::~Character() {
    if (player == this) {
        player = nullptr;
    }
}

void Character::Start() {
    GameObject* gunGO = new GameObject();
    std::weak_ptr<GameObject> weak_associated = Game::GetInstance().GetState().GetObjectPtr(&associated);
    Gun* gunPtr = new Gun(*gunGO, weak_associated);
    gunGO->AddComponent(std::unique_ptr<Gun>(gunPtr));
    std::weak_ptr<GameObject> weak_gun = Game::GetInstance().GetState().AddObject(gunGO);
    this->gun = weak_gun;
}

void Character::Update(float dt) {
    deathTimer.Update(dt);
    Animator* animator = associated.GetComponent<Animator>();
    bool isMoving = false;

    while (!taskQueue.empty()) {
        Command& currentTask = taskQueue.front();

        if (currentTask.type == CommandType::MOVE) {
            Vec2 destination = currentTask.pos;
            Vec2 currentPos = associated.box.GetCenter();
            Vec2 diff = destination.Sub(currentPos);

            if (diff.Magnitude() < 5.0f) {
                speed = {0, 0};
                taskQueue.pop();
            } else {
                speed = diff.Normalize().Mul(linearSpeed);
                isMoving = true;
                break;
            }
        } 
        else if (currentTask.type == CommandType::SHOOT) {
            auto gunPtr = gun.lock();
            if (gunPtr) {
                Gun* g = (Gun*)gunPtr->GetComponent<Gun>();
                if (g) g->Shoot(currentTask.pos);
            }
            taskQueue.pop();
        }
    }
    

    if (hp > 0) {
        associated.box.SetX(associated.box.GetX() + speed.GetX() * dt);
        associated.box.SetY(associated.box.GetY() + speed.GetY() * dt);

        if (animator) {
            if (isMoving) animator->SetAnimation("walking");
            else animator->SetAnimation("idle");
        }
    } else {
        speed = {0, 0};
        if (animator) animator->SetAnimation("dead");
        
        if (deathTimer.Get() > 2.0f) {
            associated.RequestDelete();
        }
    }
}

void Character::Render() {}

void Character::Issue(Command task) {
    taskQueue.push(task);
}