#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "Sound.h"


class Zombie : public Component {
    private:
        int hitpoints;
        Sound deathSound;
        Sound hitSound;
    public:
        Zombie(GameObject& associated);
        void Damage(int damage);
        void Update(float dt);
        void Render();
};

#endif // ZOMBIE_H