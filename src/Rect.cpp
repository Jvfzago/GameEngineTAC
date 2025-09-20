#include "Rect.h"

Rect::Rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {

}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {

}

Rect::~Rect() {

}

float Rect::GetX() const {
    return x;
}
float Rect::GetY() const {
    return y;
}
float Rect::GetW() const {
    return w;
}
float Rect::GetH() const {
    return h;
}
void Rect::SetX(float x) {
    this->x = x;
}
void Rect::SetY(float y) {
    this->y = y;
}
void Rect::SetW(float w) {
    this->w = w;
}
void Rect::SetH(float h) {
    this->h = h;
}



