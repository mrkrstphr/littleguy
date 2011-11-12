#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <SDL/SDL.h>
#include <time.h>

#include "Sprite.h"

class Character {
    private:
        int m_currentX, m_currentY;
        int m_destX, m_destY;
        int m_width, m_height;

        // retarded and temporary:
        int m_mapWidth, m_mapHeight;

        int velocity;

        Sprite *m_currentSprite;
        int m_currentFrame;

        Sprite *m_spriteRight, *m_spriteLeft;
        Sprite *m_spriteUp, *m_spriteDown;
        Sprite *m_spriteUpRight, *m_spriteUpLeft;
        Sprite *m_spriteDownRight, *m_spriteDownLeft;
        
        SDL_Rect m_position;
    
    public:
        Character(int, int, int, int);
        ~Character();

        SDL_Surface *getCurrentSprite();

        int getX();
        int getY();

        int getWidth();
        int getHeight();
        
        SDL_Rect getPosition();

        void tick();
};

#endif
