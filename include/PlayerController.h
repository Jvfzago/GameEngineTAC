#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Component.h"
#include "GameObject.h"

class PlayerController : public Component {
    public:
        PlayerController(GameObject& associated);
        
        void Start() override;
        void Update(float dt) override;
        void Render() override;
};

#endif