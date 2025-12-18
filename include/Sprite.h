#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Vec2.h"

#include <string>


class Sprite{
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;

        int frameCountW;
        int frameCountH;

        SDL_RendererFlip flip;
        Vec2 scale;
    public:
        Sprite();
        Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
        ~Sprite();
        
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y, int w, int h, double angle = 0.0f);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        
        void SetFrame(int frame);
        void SetFrameCount(int frameCountW, int frameCountH);
        
        void SetScale(float scaleX, float scaleY);
        Vec2 GetScale();
        void SetFlip(SDL_RendererFlip flip);
        bool cameraFollower;
};

#endif // SPRITE_H