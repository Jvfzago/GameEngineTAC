#ifndef STATE_H
#define STATE_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include "Sprite.h"
#include "Music.h"

#include "GameObject.h"

#include <vector>
#include <memory>

class State{
    private:
        Music music;
        bool quitRequested;

        std::vector<std::unique_ptr<GameObject>> objectArray;
    public:
        State();
        ~State();
        
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

        void AddObject(GameObject* go);
};

#endif // STATE_H