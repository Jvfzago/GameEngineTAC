#ifndef COMPONENT_H
#define COMPONENT_H


class GameObject;

class Component {
    public:
        Component(GameObject& associated);
        virtual ~Component();

        void virtual Update(float dt) = 0;
        void virtual Render() = 0;

    protected:
        GameObject& associated;
};

#endif // COMPONENT_H