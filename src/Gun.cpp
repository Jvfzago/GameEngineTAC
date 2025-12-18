#include "Gun.h"
#include "InputManager.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include <cmath>

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character) 
    : Component(associated),
      shotSound("Recursos/audio/Range.wav"),
      reloadSound("Recursos/audio/PumpAction.mp3"),
      cooldownState(0),
      cdTimer(),
      character(character),
      angle(0) 
{
    SpriteRenderer* spriteRenderer = new SpriteRenderer(associated, "Recursos/img/Gun.png", 3, 2);
    associated.AddComponent(std::unique_ptr<SpriteRenderer>(spriteRenderer));

    Animator* animator = new Animator(associated);
    associated.AddComponent(std::unique_ptr<Animator>(animator));

    animator->AddAnimation("idle", Animation(0, 0, 0.0f));
    animator->AddAnimation("reloading", Animation(1, 5, 0.1f));

    animator->SetAnimation("idle");
}

void Gun::Start() {
    // Initialization if needed
}

void Gun::Update(float dt) {
    auto owner = character.lock();
    if (!owner) {
        associated.RequestDelete();
        return;
    }

    Vec2 ownerCenter = owner->box.GetCenter();
    associated.box.SetCenter(ownerCenter);

    float offset = 30.0f;
    associated.box.SetX(associated.box.GetX() + cos(angle) * offset);
    associated.box.SetY(associated.box.GetY() + sin(angle) * offset);

    cdTimer.Update(dt);
    Animator* animator = (Animator*)associated.GetComponent<Animator>();

    switch (cooldownState) {
        case 0: //idle
            break;

        case 1: //delay para recarregar
            if (cdTimer.Get() > 0.2f) {
                cooldownState = 2;
                cdTimer.Restart();
                
                reloadSound.Play();
                if (animator) animator->SetAnimation("reloading");
            }
            break;

        case 2: //recarregando
            if (cdTimer.Get() > 0.4f) {
                cooldownState = 3;
                cdTimer.Restart();
                
                if (animator) animator->SetAnimation("idle");
            }
            break;

        case 3: //finalizando recarga
            if (cdTimer.Get() > 0.1f) {
                cooldownState = 0;
            }
            break;
    }
}

void Gun::Render() {}

void Gun::Shoot(Vec2 target) {
    if (cooldownState == 0) {
        Vec2 gunCenter = associated.box.GetCenter();
        Vec2 direction = target.Sub(gunCenter).Normalize();

        shotSound.Play();
        cooldownState = 1;
        cdTimer.Restart();
    }
}