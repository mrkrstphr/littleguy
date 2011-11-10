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
#define SCREEN_HEIGHT 240
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
    SDL_Rect dest;

    // compute the number of tiles we need:
    int numTilesW = (SCREEN_WIDTH / TILE_SIZE);
    int numTilesH = (SCREEN_HEIGHT / TILE_SIZE);

    int xRegion = (SCREEN_WIDTH / 2) - (m_character->getGraphicWidth() / 2);
    int yRegion = (SCREEN_HEIGHT / 2) - (m_character->getGraphicHeight() / 2);

    int characterPosX = (m_character->getCharacterX() + (SCREEN_WIDTH / 2)) + (m_character->getGraphicWidth() / 2);
    int characterPosY = (m_character->getCharacterY() + (SCREEN_HEIGHT / 2)) + (m_character->getGraphicHeight() / 2);

    // increase tile count if we don't fit perfectly:
    if (SCREEN_WIDTH % TILE_SIZE != 0) numTilesW++;
    if (SCREEN_HEIGHT % TILE_SIZE != 0) numTilesH++;

    if (characterPosX >= (m_level->getMapWidth() * TILE_SIZE))
        m_offsetX = (m_level->getMapWidth() * TILE_SIZE) - SCREEN_WIDTH;
    else if (m_character->getCharacterX() > xRegion)
        m_offsetX = abs(m_character->getCharacterX() - xRegion);

    if (characterPosY >= (m_level->getMapHeight() * TILE_SIZE))
        m_offsetY = (m_level->getMapWidth() * TILE_SIZE) - SCREEN_HEIGHT;
    else if (m_character->getCharacterY() > yRegion)
        m_offsetY = abs(m_character->getCharacterY() - yRegion);

    // compute how far off the screen the first tile is:
    int tileOffsetX = (m_offsetX % TILE_SIZE);
    int tileOffsetY = (m_offsetY % TILE_SIZE);

    // handle condition of split tiles:
    if (tileOffsetX != 0) numTilesW++;
    if (tileOffsetY != 0) numTilesH++;

    if ((numTilesH - 1) + (m_offsetX / TILE_SIZE) > m_level->getMapHeight() * TILE_SIZE) {
       printf("TileHeight is out-of-bounds...\n");
       system("pause");
       exit(1);
    }

    printf("   Finished needless calculation...\n");

    // ********** draw the world (tiles):
    for (int i = 0; i < numTilesW; i++) {
        for (int j = 0; j < numTilesH; j++) {
            // find the current tile:
            if (j >= m_level->getMapHeight())
               break;

            //assert(j < m_level->getMapHeight());

            int t = m_level->getTileAt(i + (m_offsetX / TILE_SIZE), j + (m_offsetY / TILE_SIZE));


            dest.x = i * TILE_SIZE - tileOffsetX; dest.y = j * TILE_SIZE - tileOffsetY;
            dest.w = TILE_SIZE; dest.h = TILE_SIZE;

            if (t == 0)
                SDL_BlitSurface(grass, NULL, screen, &dest);
            else
                SDL_BlitSurface(dirt, NULL, screen, &dest);

            printf("Max: %d, Current: %d\n", m_level->getMapHeight(), j);
        }
    }

    printf("   Finished drawing the map...\n");

    // ********** draw the character:

    if (m_character->getCharacterX() < xRegion)
        dest.x = m_character->getCharacterX();
    else
        dest.x = xRegion;

    if (m_character->getCharacterY() < yRegion)
        dest.y = m_character->getCharacterY();
    else
        dest.y = yRegion;

    //printf("L: %d, +SW:%d, M:%d\n", m_character->getCharacterX(),
    //    m_character->getCharacterX() + (SCREEN_WIDTH / 2),
    //    m_level->getMapWidth() * TILE_SIZE);

    if ((m_character->getCharacterX() + (SCREEN_WIDTH / 2))
      + (m_character->getGraphicWidth() / 2) >= (m_level->getMapWidth() * TILE_SIZE)) {
        //dest.x = SCREEN_WIDTH - ((m_level->getMapWidth() * TILE_SIZE) - m_character->getCharacterX());
    }

    if ((m_character->getCharacterY() + (SCREEN_HEIGHT / 2))
     >= (m_level->getMapHeight() * TILE_SIZE))
        printf("STOP! STOP! STOP!\n");

    dest.w = 96; dest.h = 96;

    SDL_BlitSurface(m_character->getCurrentSprite(), NULL, screen, &dest);

    // ********** update the screen:
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
        printf("Character has updated...\n");

        /* Draw to screen */
        draw();
        printf("Draw() has finished...\n");

        printf("Successful finish...\n\n");

        SDL_Delay(80);
    }

    delete m_character;
    delete m_level;

    return 0;
}
