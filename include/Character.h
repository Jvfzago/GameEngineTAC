#ifndef CHARACTER_H
#define CHARACTER_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"

#include <string>
#include <queue>
#include <memory>

class Character : public Component {
    public:
        enum class CommandType { MOVE, SHOOT };

        class Command {
            public:
                Command(CommandType type, float x, float y)
                 : type(type), pos(x, y) {}
                CommandType type;
                Vec2 pos;
        };

        Character(GameObject& associated, std::string sprite);
        ~Character();

        void Start() override;
        void Update(float dt) override;
        void Render() override;

        void Issue(Command task);

        GameObject* GetAssociated();

        static Character* player;

        void ClearCommands();

    private:
        std::weak_ptr<GameObject> gun;
        std::queue<Command> taskQueue;
        Vec2 speed;
        float linearSpeed;
        int hp;
        Timer deathTimer;
};

#endif