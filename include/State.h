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

        std::vector<std::shared_ptr<GameObject>> objectArray;

        bool started;
    public:
        State();
        ~State();
        
        bool QuitRequested();
        void Start();
        void LoadAssets();
        void Update(float dt);
        void Render();

        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);


};

#endif // STATE_H