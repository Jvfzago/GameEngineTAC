#include "Animator.h"
#include "SpriteRenderer.h"



Animator::Animator(GameObject& associated) : Component(associated), frameStart(0), frameEnd(0), frameTime(0), currentFrame(0), timeElapsed(0) {}

void Animator::Update(float dt) {
    if (animations.empty()) return;
    if (frameTime <= 0) return;
    timeElapsed += dt;
    if (timeElapsed >= frameTime) {
        timeElapsed -= frameTime;
        currentFrame++;
        if (currentFrame > frameEnd) {
            currentFrame = frameStart;
        }
        
        auto sprite = associated.GetComponent<SpriteRenderer>();
        if (sprite) {
            sprite->SetFrame(currentFrame);
        }
    }
}

void Animator::Render() {
    
}

void Animator::SetAnimation(std::string name) {
    auto it = animations.find(name);
    if (it != animations.end()) {
        Animation& anim = it->second;
        frameStart = anim.GetFrameStart();
        frameEnd = anim.GetFrameEnd();
        frameTime = anim.GetFrameTime();
        currentFrame = frameStart;
        timeElapsed = 0;

        auto sprite = associated.GetComponent<SpriteRenderer>();
        if (sprite) {
            sprite->SetFrame(currentFrame);
        }
    }
}

void Animator::AddAnimation(std::string name, Animation anim) {
    animations[name] = anim;
}

