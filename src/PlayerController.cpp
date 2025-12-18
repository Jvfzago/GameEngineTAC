#include "PlayerController.h"
#include "InputManager.h"
#include "Character.h"
#include "Camera.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {}

void PlayerController::Start() {}

void PlayerController::Update(float dt) {
    if (Character::player == nullptr) return;

    InputManager& input = InputManager::GetInstance();
    
    Vec2 direction(0, 0);
    if (input.IsKeyDown(SDLK_w)) {
        direction.SetY(direction.GetY() - 1);
    }
    if (input.IsKeyDown(SDLK_s)) {
        direction.SetY(direction.GetY() + 1);
    }
    if (input.IsKeyDown(SDLK_a)) {
        direction.SetX(direction.GetX() - 1);
    }
    if (input.IsKeyDown(SDLK_d)) {
        direction.SetX(direction.GetX() + 1);
    }

    if (direction.Magnitude() > 0) {
        direction = direction.Normalize();
        Vec2 currentPos = Character::player->GetAssociated()->box.GetCenter();
        Vec2 targetPos = currentPos.Add(direction.Mul(10.0f));

        Character::player->ClearCommands();
        
        Character::Command moveCmd(Character::CommandType::MOVE, targetPos.GetX(), targetPos.GetY());
        Character::player->Issue(moveCmd);
    }

    if (input.MousePress(SDL_BUTTON_LEFT)) {
        float mouseWorldX = (float)input.GetMouseX() + Camera::pos.GetX();
        float mouseWorldY = (float)input.GetMouseY() + Camera::pos.GetY();
        
        Character::Command shootCmd(Character::CommandType::SHOOT, mouseWorldX, mouseWorldY);
        Character::player->Issue(shootCmd);
    }
}

void PlayerController::Render() {}