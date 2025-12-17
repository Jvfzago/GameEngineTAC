#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component {
    private:
        int hitpoints;
        Sound deathSound;
        Sound hitSound;
        Timer hitTimer;
        Timer deathTimer;

        bool hit;
    public:
        Zombie(GameObject& associated);
        void Damage(int damage);
        
        void Start() override;
        void Update(float dt) override;
        void Render() override;
};

#endif // ZOMBIE_H