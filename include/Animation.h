#ifndef ANIMATION_H
#define ANIMATION_H



class Animation {
   private:
    int frameStart;
    int frameEnd;
    int frameTime;

   public:
    Animation() = default;
    Animation(int frameStart, int frameEnd, int frameTime);

    int GetFrameStart() const;
    int GetFrameEnd() const;
    int GetFrameTime() const;
    
};

#endif  // ANIMATION_H