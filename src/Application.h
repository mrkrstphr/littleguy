#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <vector>

#include "Character.h"
#include "Level.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 32

class Application {
    private:
        SDL_Surface *screen;
        SDL_Surface *grass;
        SDL_Surface *dirt;
        
        SDL_Rect destination;
        SDL_Rect location;
        
        Character *m_character;
        
        Level *m_level;

int m_offsetX, m_offsetY;

    public:
        Application();
        ~Application();
        
        void draw();
        void run();
};

#endif
