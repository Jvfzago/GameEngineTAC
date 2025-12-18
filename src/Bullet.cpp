#include "Bullet.h"
#include "SpriteRenderer.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated), speed(0,0), damage(0), distanceLeft(0)
{
    this->damage = damage;
    this->distanceLeft = maxDistance;

    this->speed = Vec2(cos(angle) * speed, sin(angle) * speed);

    SpriteRenderer* sprite = new SpriteRenderer(associated, "Recursos/img/Bullet.png");
    associated.AddComponent(std::unique_ptr<SpriteRenderer>(sprite));
    //associated.angleDeg = angle * (180 / M_PI);
}

void Bullet::Start() {}

void Bullet::Update(float dt)
{
    Vec2 distance = speed.Mul(dt);
    associated.box.SetX(associated.box.GetX() + distance.GetX());
    associated.box.SetY(associated.box.GetY() + distance.GetY());

    distanceLeft -= distance.Magnitude();
    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

int Bullet::GetDamage() {
    return damage;
}