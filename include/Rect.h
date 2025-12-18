#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
    private:
        float x;
        float y;
        float w;
        float h;
    public:
        Rect();
        Rect(float x, float y, float w, float h);
        ~Rect();

        float GetX() const;
        float GetY() const;
        float GetW() const;
        float GetH() const;
        void SetX(float x);
        void SetY(float y);
        void SetW(float w);
        void SetH(float h);

        Vec2 GetCenter() const;
        void SetCenter(const Vec2& center);

};

#endif // RECT_H