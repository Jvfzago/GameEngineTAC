#include "Animation.h"

Animation::Animation(int frameStart, int frameEnd, float frameTime) :
frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime) {
    
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