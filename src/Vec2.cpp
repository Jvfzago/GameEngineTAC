#include "Vec2.h"

Vec2::Vec2() : x(0.0f), y(0.0f) {

}

Vec2::Vec2(float x, float y) : x(x), y(y) {

}

Vec2::~Vec2() {

}

float Vec2::GetX() const {
    return x;
}

float Vec2::GetY() const {
    return y;
}

void Vec2::SetX(float x) {
    this->x = x;
}

void Vec2::SetY(float y) {
    this->y = y;
}

float Vec2::Length() const {
    return std::sqrt(x*x + y*y);
}

Vec2 Vec2::Normalize() const {
    float len = Length();
    if(len == 0) return Vec2(0, 0);
    return Vec2(x/len, y/len);
}

Vec2 Vec2::Add(const Vec2& v) const {
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::Sub(const Vec2& v) const {
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::Mul(float scalar) const {
    return Vec2(x*scalar, y*scalar);
}

Vec2 Vec2::Div(float scalar) const {
    if(scalar == 0) throw std::runtime_error("Division by zero in Vec2::Div");
    return Vec2(x/scalar, y/scalar);
}

float Vec2::Dot(const Vec2& v) const {
    return x*v.x + y*v.y;
}

float Vec2::Angle(const Vec2& v) const {
    float dotProd = Dot(v);
    float lengths = Length() * v.Length();
    if(lengths == 0) throw std::runtime_error("Division by zero in Vec2::Angle");
    float cosAngle = dotProd / lengths;
    if(cosAngle > 1.0f) cosAngle = 1.0f;
    if(cosAngle < -1.0f) cosAngle = -1.0f;
    return std::acos(cosAngle);
}

float Vec2::AngleWithXAxis() const{
    return std::atan2(y, x);
}

Vec2 Vec2::Rotate(float angle) const {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    return Vec2(x*cosA - y*sinA, y*cosA + x*sinA);
}

std::string Vec2::ToString() const {
    return "Vec2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

float Vec2::Magnitude() const {
    return std::sqrt(x * x + y * y);
}
