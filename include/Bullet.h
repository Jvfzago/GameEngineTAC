#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include <string>

class Bullet : public Component {
    public:
        Bullet(GameObject& associated, 
            float angle, 
            float speed, 
            int damage, 
            float maxDistance);
            
        void Start() override;
        void Update(float dt) override;
        void Render() override;
        int GetDamage();

    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
};

#endif