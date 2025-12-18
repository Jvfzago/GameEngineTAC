#include "Camera.h"
#include "InputManager.h"

Vec2 Camera::pos = {0, 0};
Vec2 Camera::speed = {0, 0};
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if(focus != nullptr) {
        pos.SetX(focus->box.GetX() + focus->box.GetW()/2 - 600); 
        //Mudar caso queria mudar tamanho da tela
        pos.SetY(focus->box.GetY() + focus->box.GetH()/2 - 450); 
        //Mudar caso queria mudar tamanho da tela
    } else {
        float linearSpeed = 200.0f;
        speed.SetX(0);
        speed.SetY(0);
        
        if (InputManager::GetInstance().IsKeyDown(SDLK_UP)){
            speed.SetY(-linearSpeed);
        }
        else if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN)){
            speed.SetY(linearSpeed);
        }

        if (InputManager::GetInstance().IsKeyDown(SDLK_LEFT)){
            speed.SetX(-linearSpeed);
        }
        else if (InputManager::GetInstance().IsKeyDown(SDLK_RIGHT)){
            speed.SetX(linearSpeed);
        }

        pos = pos.Add(speed.Mul(dt));
    }
}

GameObject* Camera::GetFocus() {
    return focus;
}