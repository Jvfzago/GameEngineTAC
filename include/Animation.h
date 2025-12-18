#ifndef ANIMATION_H
#define ANIMATION_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class Animation {
   private:
    int frameStart;
    int frameEnd;
    float frameTime;

   public:
    Animation() = default;
    Animation(int frameStart, 
        int frameEnd, float frameTime, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int GetFrameStart() const;
    int GetFrameEnd() const;
    float GetFrameTime() const;
    
    SDL_RendererFlip flip;
};

#endif  // ANIMATION_H