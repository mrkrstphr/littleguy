#ifndef __SPRITE_H
#define __SPRITE_H

#include <vector>
#include <SDL/SDL.h>

class Sprite {
    private:
        std::vector<SDL_Surface*> m_frames;

    public:
        Sprite();
        ~Sprite();

        SDL_Surface *getFrame(int);

        void load(SDL_Surface*);

        int getFrameCount();
};

#endif
