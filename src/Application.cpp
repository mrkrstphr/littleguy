#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "Application.h"

Application::Application()
    : screen(NULL), grass(NULL), dirt(NULL)
{

}

Application::~Application()
{
    
}

void Application::run()
{
    int done;
    
    /* Initialize SDL */
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
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

    m_character = new Character(0, 0, m_level->getWidth() * TILE_SIZE,
        m_level->getHeight() * TILE_SIZE);

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
}

/* This function draws to the screen; replace this with your own code! */
void Application::draw () {
    
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
        if (position.y + (position.h / 2) > (m_level->getHeight() * TILE_SIZE) - (SCREEN_HEIGHT / 2)) {
            // he is @ screen - (size of map - position)
            position.y = SCREEN_HEIGHT - ((m_level->getHeight() * TILE_SIZE) - position.y);
            
            map.y = character.y - position.y;
        } else {
            // he is centered
            position.y = (SCREEN_HEIGHT / 2) - (position.h / 2);
            
            map.y = character.y - position.y;
        }
    }
    
    if (position.x + (position.w / 2) <= (SCREEN_WIDTH / 2)) {
        // he is where he is
    } else {
        if (position.x + (position.w / 2) > (m_level->getWidth() * TILE_SIZE) - (SCREEN_WIDTH / 2)) {
            // he is @ screen - (size of map - position)
            position.x = SCREEN_WIDTH - ((m_level->getWidth() * TILE_SIZE) - position.x);
            
            map.x = character.x - position.x;
        } else {
            // he is centered
            position.x = (SCREEN_WIDTH / 2) - (position.w / 2);
            
            map.x = character.x - position.x;
        }
    }
    
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
    
    if ((map.y / TILE_SIZE) + numTilesY > m_level->getHeight()) {
        printf("REDUCING\n");
        map.y -= TILE_SIZE;
    }
    
    for (int x = 0; x <= numTilesX; x++) {
            
        int tileX = (map.x / TILE_SIZE) + x;
        
        if (tileX > m_level->getWidth() - 1) {
            // TODO FIXME How are we even getting here?
            printf("Detected a problem: %d > %d\n", tileX, m_level->getWidth() - 1);
            continue;
        }
        
        for (int y = 0; y <= numTilesY; y++) {
            
            int tileY = (map.y / TILE_SIZE) + y;
            
            if (tileY > m_level->getHeight() - 1) {
                // TODO FIXME How are we even getting here?
                printf("Detected a problem: %d > %d\n", tileY, m_level->getHeight() - 1);
                continue;
            }
            
            int t = m_level->getTileAt(tileX, tileY);
            
            SDL_Rect dest;
            
            dest.w = TILE_SIZE; 
            dest.h = TILE_SIZE;
            dest.x = (x * TILE_SIZE) - (map.x % TILE_SIZE); 
            dest.y = (y * TILE_SIZE) - (map.y % TILE_SIZE);

            if (t == 0)
                SDL_BlitSurface(grass, NULL, screen, &dest);
            else
                SDL_BlitSurface(dirt, NULL, screen, &dest);
        }
    }
    
    SDL_BlitSurface(m_character->getCurrentSprite(), NULL, screen, &position);
    SDL_Flip(screen);
}
