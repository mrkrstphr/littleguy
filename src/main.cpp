#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <SDL/SDL.h>

#include <time.h>

#ifdef   main
#undef   main
#endif

#include "Character.h"
#include "Level.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 256
#define TILE_SIZE 32

SDL_Surface *screen = NULL;
SDL_Surface *grass = NULL;
SDL_Surface *dirt = NULL;

SDL_Rect destination;
SDL_Rect location;

Character *m_character;

Level *m_level;

int m_offsetX, m_offsetY;

/* This function draws to the screen; replace this with your own code! */
static void draw () {
    
    // Where is our character?
    
    SDL_Rect character = m_character->getPosition();
    SDL_Rect position = character;
    SDL_Rect map;
    
    map.w = SCREEN_WIDTH; 
    map.h = SCREEN_HEIGHT;
    map.x = 0; 
    map.y = 0;
    
    // X
    
    /*
    if (character position < center of screen) {
        he is where he is
    } else if (character position > center of screen) {
        if (character position > width of the map - half the screen) {
            he is where he is @ screen - (size of map - position)
        } else {
            he is centered
        }
    } 
    */
    
    if (position.y + (position.h / 2) <= (SCREEN_HEIGHT / 2)) {
        // he is where he is
    } else {
        if (position.y + (position.h / 2) > (m_level->getMapHeight() * TILE_SIZE) - (SCREEN_HEIGHT / 2)) {
            // he is @ screen - (size of map - position)
            position.y = SCREEN_HEIGHT - ((m_level->getMapHeight() * TILE_SIZE) - position.y);
            
            map.y = character.y - position.y;
        } else {
            // he is centered
            position.y = (SCREEN_HEIGHT / 2) - (position.h / 2);
            
            map.y = character.y - position.y;
        
            //printf("testing: [%d vs %d]\n", character.y, position.y);
        }
    }
    
    /*
    if (position.x + (position.w / 2) <= (SCREEN_WIDTH / 2)) {
        // he is where he is
    } else {
        if (position.x + (position.h / 2) > (m_level->getMapWidth() * TILE_SIZE) - (SCREEN_WIDTH / 2)) {
            // he is @ screen - (size of map - position)
            position.x = SCREEN_WIDTH - ((m_level->getMapWidth() * TILE_SIZE) - position.x);
            
            map.x = character.x - position.x;
        } else {
            // he is centered
            position.x = (SCREEN_WIDTH / 2) - (position.w / 2);
            
            map.x = character.x - position.x;
        
            printf("testing: [%d vs %d]\n", character.x, position.x);
        }
    }
    */
    
    
    int numTilesX = SCREEN_WIDTH / TILE_SIZE;
    int numTilesY = SCREEN_HEIGHT / TILE_SIZE;
    
    if (map.x % TILE_SIZE > 0)
    {
        numTilesX++;
    }
    
    if (map.y % TILE_SIZE > 0)
    {
        numTilesY++;
    }
    
    if ((map.y / TILE_SIZE) + numTilesY > m_level->getMapHeight()) {
        printf("REDUCING\n");
        map.y -= TILE_SIZE;
    }
    
    /*
    for (int x = 0; x <= numTilesX; x++) {
        for (int y = 0; y <= numTilesY; y++) {
            
            int tileY = (map.y / TILE_SIZE) + y;
            
            //printf("map: [%d,%d], tile_x: [%d,%d]\n", x, y, tileX, tileY);
            
            printf("getTileAt(%d, %d);\n", x, tileY);
            
            //continue;
            
            if (tileY >= m_level->getMapHeight()) {
                printf("Detected a problem: %d >= %d\n", tileY, m_level->getMapHeight());
            }
            
            int t = m_level->getTileAt(x, tileY);
            
            SDL_Rect dest;
            
            dest.w = TILE_SIZE; 
            dest.h = TILE_SIZE;
            dest.x = (x * TILE_SIZE) - (map.x % TILE_SIZE); 
            dest.y = (y * TILE_SIZE) - (map.y % TILE_SIZE);

            //dest.x = i * TILE_SIZE - tileOffsetX; dest.y = j * TILE_SIZE - tileOffsetY;
            //dest.w = TILE_SIZE; dest.h = TILE_SIZE;

            printf(":== Drawing Tile @ [%d,%d]\n", dest.x, dest.y);
            if (t == 0)
                SDL_BlitSurface(grass, NULL, screen, &dest);
            else
                SDL_BlitSurface(dirt, NULL, screen, &dest);
        }
    }
    */
    
    SDL_BlitSurface(m_character->getCurrentSprite(), NULL, screen, &position);
    SDL_Flip(screen);
}

int main (int argc, char *argv[]) {
    int done;

    srand(time(NULL));

    /* Initialize SDL */
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError ());
        exit(1);
    }

    atexit (SDL_Quit);

    /* Set 640x480 16-bits video mode */
    screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)     {
        printf("Couldn't set 640x480x16 video mode: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_WM_SetCaption ("LittleGuy", NULL);

    m_level = new Level("map.txt");

    if (m_level == NULL) {
       printf("Failed to load level.\n");
       system("pause");
       exit(1);
    }

    grass = SDL_LoadBMP("graphics/grass.bmp");
    dirt = SDL_LoadBMP("graphics/dirt.bmp");

    if (grass == NULL || dirt == NULL) {
       printf("Failed to load graphics.\n");
       system("pause");
       exit(1);
    }

    m_character = new Character(0, 0, m_level->getMapWidth() * TILE_SIZE,
        m_level->getMapHeight() * TILE_SIZE);

    done = 0;
    while (!done) {
        SDL_Event event;

        /* Check for events */
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    break;
                case SDL_QUIT:
                    done = 1;
                    break;
                default:
                    break;
            }
        }

        m_character->tick();

        /* Draw to screen */
        draw();

        SDL_Delay(80);
    }

    delete m_character;
    delete m_level;

    return 0;
}
