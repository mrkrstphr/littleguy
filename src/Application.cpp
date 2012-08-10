#include <fstream>
#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Application.h"

Application::Application()
    : screen(NULL), grass(NULL), dirt(NULL),
    m_numTilesX(0), m_numTilesY(0)
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

    SDL_WM_SetCaption("LittleGuy", NULL);

    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }


    m_level = new Level("map.txt");

    if (m_level == NULL) {
       printf("Failed to load level.\n");
       system("pause");
       exit(1);
    }

    printf("Level size: [%d,%d]\n", m_level->getWidth() * TILE_SIZE, m_level->getHeight() * TILE_SIZE);

    grass = SDL_LoadBMP("graphics/grass.bmp");
    dirt = SDL_LoadBMP("graphics/dirt.bmp");

    if (grass == NULL || dirt == NULL) {
       printf("Failed to load graphics.\n");
       system("pause");
       exit(1);
    }

    m_character = new Character(0, 0, m_level->getWidth() * TILE_SIZE,
        m_level->getHeight() * TILE_SIZE);

    m_numTilesX = ceil(SCREEN_WIDTH / TILE_SIZE);
    m_numTilesY = ceil(SCREEN_HEIGHT / TILE_SIZE);

    done = 0;
    while (!done) {
        SDL_Event event;

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

        draw();
        SDL_Delay(80);
    }

    delete m_character;
    delete m_level;
}

void Application::draw()
{
    SDL_Rect position = m_character->getPosition();
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    
    camera.x = (position.x + (m_character->getWidth() / 2)) - SCREEN_WIDTH / 2;
    camera.y = (position.y + (m_character->getHeight() / 2)) - SCREEN_HEIGHT / 2;
    
    if (camera.x < 0) {
        camera.x = 0;    
    }
    
    if (camera.y < 0) {
        camera.y = 0;    
    }
    
    if (camera.x > (m_level->getWidth() * TILE_SIZE) - camera.w) {
        camera.x = (m_level->getWidth() * TILE_SIZE) - camera.w;    
    }
    
    if (camera.y > (m_level->getHeight() * TILE_SIZE) - camera.h) {
        camera.y = (m_level->getHeight() * TILE_SIZE) - camera.h;    
    }

    for (int tX = 0; tX < m_level->getWidth(); tX++) {
        for (int tY = 0; tY < m_level->getHeight(); tY++) {
            SDL_Rect box = {tX * TILE_SIZE, tY * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            
            if (check_collision(camera, box) == true) {
                box.x = box.x - camera.x;
                box.y = box.y - camera.y;
                
                int t = m_level->getTileAt(tX, tY);
                
                if (t == 0)
                    SDL_BlitSurface(grass, NULL, screen, &box);
                else
                    SDL_BlitSurface(dirt, NULL, screen, &box);
            }
        }
    }
    
    position.x -= camera.x;
    position.y -= camera.y;
    
    SDL_BlitSurface(m_character->getCurrentSprite(), NULL, screen, &position);
    
    SDL_Flip(screen);
}


bool Application::check_collision(SDL_Rect A, SDL_Rect B)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if(leftA >= rightB) {
        return false;
    }

    return true;
}
