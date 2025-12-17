#ifndef SPRITE_H
#define SPRITE_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include <string>


class Sprite{
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;

        int frameCountW;
        int frameCountH;

        bool cameraFollwer;
    public:
        Sprite();
        Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
        ~Sprite();

        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y, int w, int h);
        int GetWidth();
        int GetHeight();
        bool IsOpen();

        void SetFrame(int frame); // frame = 0..(frameCountW*frameCountH - 1)
        void SetFrameCount(int frameCountW, int frameCountH);
        
};

#endif // SPRITE_H