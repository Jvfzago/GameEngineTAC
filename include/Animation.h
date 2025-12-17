#ifndef ANIMATION_H
#define ANIMATION_H



class Animation {
   private:
    int frameStart;
    int frameEnd;
    float frameTime;

   public:
    Animation() = default;
    Animation(int frameStart, int frameEnd, float frameTime);

    int GetFrameStart() const;
    int GetFrameEnd() const;
    float GetFrameTime() const;
    
};

#endif  // ANIMATION_H