#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <SDL2/SDL_mixer.h>

class Sound {
    private:
        int channel;
        Mix_Chunk* chunk;
    public:
        Sound();
        Sound(std::string file);
        ~Sound();

        void Play(int times = 1);
        void Stop();
        void Open(std::string file);
        bool IsOpen();
        
};

#endif  // SOUND_H