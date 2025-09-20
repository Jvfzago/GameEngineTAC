#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <iostream>
#include <string>

class Vec2{
    private:
        static constexpr float PI = 3.14159265358979323846f;
        float x;
        float y;

    public:
        Vec2();
        Vec2(float x, float y);
        ~Vec2();

        float GetX() const;
        float GetY() const;
        void SetX(float x);
        void SetY(float y);
        float Length() const;
        Vec2 Normalize() const;
        Vec2 Add(const Vec2& v) const;
        Vec2 Sub(const Vec2& v) const;
        Vec2 Mul(float scalar) const;
        Vec2 Div(float scalar) const;
        float Dot(const Vec2& v) const;
        float Angle(const Vec2& v) const; // Radians
        float AngleWithXAxis() const; // Radians
        Vec2 Rotate(float angle) const; // Radians, rotates clockwise, causes y goes down
        std::string ToString() const;

};

#endif // VEC2_H