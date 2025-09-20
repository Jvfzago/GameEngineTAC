#include "Animation.h"

Animation::Animation(int frameStart, int frameEnd, int frameTime) :
frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime) {
    
}

int Animation::GetFrameStart() const {
    return frameStart;
}
int Animation::GetFrameEnd() const {
    return frameEnd;
}
int Animation::GetFrameTime() const {
    return frameTime;
}