#include "Animation.h"

Animation::Animation(int frameStart, int frameEnd, float frameTime, SDL_RendererFlip flip)
    :
frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime), flip(SDL_FLIP_NONE) {
    
}

int Animation::GetFrameStart() const {
    return frameStart;
}
int Animation::GetFrameEnd() const {
    return frameEnd;
}
float Animation::GetFrameTime() const {
    return frameTime;
}