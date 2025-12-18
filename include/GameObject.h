#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Component.h"
#include "Rect.h"
#include <vector>
#include <memory>

class GameObject {
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;

        bool started;
    public:
        GameObject();
        ~GameObject();

        void Start();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(std::unique_ptr<Component>&& cpt);
        void RemoveComponent(Component* cpt);

        template<typename T>
        T* GetComponent(){
            long unsigned int index;
            for(index=0;index<components.size();index++){
                T* component = dynamic_cast<T*>(components[index].get());
                if(component != nullptr){
                    return component;
                }
            }
            return nullptr;
        }

        Rect box;
        double angleDeg;

};

#endif // GAMEOBJECT_H