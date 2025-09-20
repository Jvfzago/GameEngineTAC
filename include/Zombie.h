#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"

class Zombie : public Component {
    private:
        int hitpoints;
    public:
        Zombie(GameObject& associated);
        void Damage(int damage);
        void Update(float dt);
        void Render();
};

#endif // ZOMBIE_H