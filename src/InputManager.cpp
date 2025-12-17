#include "InputManager.h"

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager() : mouseState{}, mouseUpdate{},
    quitRequested(false),
    updateCounter(0),
    mouseX(0),
    mouseY(0) {} //unordered_map não deve ser inicializado

InputManager::~InputManager() {}

void InputManager::Update(){
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Event event;
    updateCounter++;
    quitRequested = false;

    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_KEYDOWN:
            if( event.key.repeat != 0 ) break;
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button<6) {
                    mouseState[event.button.button] = true;
                    mouseUpdate[event.button.button] = updateCounter;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button<6) {
                    mouseState[event.button.button] = false;
                    mouseUpdate[event.button.button] = updateCounter;
                }
                break;
            case SDL_QUIT:
                quitRequested = true;
                break;
            default:
                break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return (keyUpdate[key] == updateCounter && keyState[key] == true);
}

bool InputManager::KeyRelease(int key) {
    return (keyUpdate[key] == updateCounter && keyState[key] == false);
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key] == true;
}

bool InputManager::MousePress(int key) {
    return (mouseUpdate[key] == updateCounter && mouseState[key] == true);
}

bool InputManager::MouseRelease(int key) {
    return (mouseUpdate[key] == updateCounter && mouseState[key] == false);
}

bool InputManager::IsMouseDown(int key) {
    return mouseState[key] == true;
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}