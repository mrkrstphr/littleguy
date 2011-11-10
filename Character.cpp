#include "Character.h"

Character::Character(int locationX, int locationY, int mapWidth, int mapHeight)
 : m_currentX(locationX), m_currentY(locationY),
   m_destX(locationX), m_destY(locationY),
   m_mapWidth(mapWidth), m_mapHeight(mapHeight), m_currentFrame(0)
{
    m_spriteRight = new Sprite();
    m_spriteRight->load(SDL_LoadBMP("graphics/boy/walking_e00.bmp"));
    m_spriteRight->load(SDL_LoadBMP("graphics/boy/walking_e01.bmp"));
    m_spriteRight->load(SDL_LoadBMP("graphics/boy/walking_e02.bmp"));
    m_spriteRight->load(SDL_LoadBMP("graphics/boy/walking_e03.bmp"));
    m_spriteRight->load(SDL_LoadBMP("graphics/boy/walking_e04.bmp"));
    m_spriteRight->load(SDL_LoadBMP("graphics/boy/walking_e05.bmp"));
    m_spriteRight->load(SDL_LoadBMP("graphics/boy/walking_e06.bmp"));
    m_spriteRight->load(SDL_LoadBMP("graphics/boy/walking_e07.bmp"));

    m_spriteLeft = new Sprite();
    m_spriteLeft->load(SDL_LoadBMP("graphics/boy/walking_w00.bmp"));
    m_spriteLeft->load(SDL_LoadBMP("graphics/boy/walking_w01.bmp"));
    m_spriteLeft->load(SDL_LoadBMP("graphics/boy/walking_w02.bmp"));
    m_spriteLeft->load(SDL_LoadBMP("graphics/boy/walking_w03.bmp"));
    m_spriteLeft->load(SDL_LoadBMP("graphics/boy/walking_w04.bmp"));
    m_spriteLeft->load(SDL_LoadBMP("graphics/boy/walking_w05.bmp"));
    m_spriteLeft->load(SDL_LoadBMP("graphics/boy/walking_w06.bmp"));
    m_spriteLeft->load(SDL_LoadBMP("graphics/boy/walking_w07.bmp"));

    m_spriteUp = new Sprite();
    m_spriteUp->load(SDL_LoadBMP("graphics/boy/walking_n00.bmp"));
    m_spriteUp->load(SDL_LoadBMP("graphics/boy/walking_n01.bmp"));
    m_spriteUp->load(SDL_LoadBMP("graphics/boy/walking_n02.bmp"));
    m_spriteUp->load(SDL_LoadBMP("graphics/boy/walking_n03.bmp"));
    m_spriteUp->load(SDL_LoadBMP("graphics/boy/walking_n04.bmp"));
    m_spriteUp->load(SDL_LoadBMP("graphics/boy/walking_n05.bmp"));
    m_spriteUp->load(SDL_LoadBMP("graphics/boy/walking_n06.bmp"));
    m_spriteUp->load(SDL_LoadBMP("graphics/boy/walking_n07.bmp"));

    m_spriteDown = new Sprite();
    m_spriteDown->load(SDL_LoadBMP("graphics/boy/walking_s00.bmp"));
    m_spriteDown->load(SDL_LoadBMP("graphics/boy/walking_s01.bmp"));

    m_spriteDown->load(SDL_LoadBMP("graphics/boy/walking_s02.bmp"));
    m_spriteDown->load(SDL_LoadBMP("graphics/boy/walking_s03.bmp"));
    m_spriteDown->load(SDL_LoadBMP("graphics/boy/walking_s04.bmp"));
    m_spriteDown->load(SDL_LoadBMP("graphics/boy/walking_s05.bmp"));
    m_spriteDown->load(SDL_LoadBMP("graphics/boy/walking_s06.bmp"));
    m_spriteDown->load(SDL_LoadBMP("graphics/boy/walking_s07.bmp"));

    m_spriteUpRight = new Sprite();
    m_spriteUpRight->load(SDL_LoadBMP("graphics/boy/walking_ne00.bmp"));
    m_spriteUpRight->load(SDL_LoadBMP("graphics/boy/walking_ne01.bmp"));
    m_spriteUpRight->load(SDL_LoadBMP("graphics/boy/walking_ne02.bmp"));
    m_spriteUpRight->load(SDL_LoadBMP("graphics/boy/walking_ne03.bmp"));
    m_spriteUpRight->load(SDL_LoadBMP("graphics/boy/walking_ne04.bmp"));
    m_spriteUpRight->load(SDL_LoadBMP("graphics/boy/walking_ne05.bmp"));
    m_spriteUpRight->load(SDL_LoadBMP("graphics/boy/walking_ne06.bmp"));
    m_spriteUpRight->load(SDL_LoadBMP("graphics/boy/walking_ne07.bmp"));

    m_spriteUpLeft = new Sprite();
    m_spriteUpLeft->load(SDL_LoadBMP("graphics/boy/walking_nw00.bmp"));
    m_spriteUpLeft->load(SDL_LoadBMP("graphics/boy/walking_nw01.bmp"));
    m_spriteUpLeft->load(SDL_LoadBMP("graphics/boy/walking_nw02.bmp"));
    m_spriteUpLeft->load(SDL_LoadBMP("graphics/boy/walking_nw03.bmp"));
    m_spriteUpLeft->load(SDL_LoadBMP("graphics/boy/walking_nw04.bmp"));
    m_spriteUpLeft->load(SDL_LoadBMP("graphics/boy/walking_nw05.bmp"));
    m_spriteUpLeft->load(SDL_LoadBMP("graphics/boy/walking_nw06.bmp"));
    m_spriteUpLeft->load(SDL_LoadBMP("graphics/boy/walking_nw07.bmp"));

    m_spriteDownRight = new Sprite();
    m_spriteDownRight->load(SDL_LoadBMP("graphics/boy/walking_se00.bmp"));
    m_spriteDownRight->load(SDL_LoadBMP("graphics/boy/walking_se01.bmp"));
    m_spriteDownRight->load(SDL_LoadBMP("graphics/boy/walking_se02.bmp"));
    m_spriteDownRight->load(SDL_LoadBMP("graphics/boy/walking_se03.bmp"));
    m_spriteDownRight->load(SDL_LoadBMP("graphics/boy/walking_se04.bmp"));
    m_spriteDownRight->load(SDL_LoadBMP("graphics/boy/walking_se05.bmp"));
    m_spriteDownRight->load(SDL_LoadBMP("graphics/boy/walking_se06.bmp"));
    m_spriteDownRight->load(SDL_LoadBMP("graphics/boy/walking_se07.bmp"));

    m_spriteDownLeft = new Sprite();
    m_spriteDownLeft->load(SDL_LoadBMP("graphics/boy/walking_sw00.bmp"));
    m_spriteDownLeft->load(SDL_LoadBMP("graphics/boy/walking_sw01.bmp"));
    m_spriteDownLeft->load(SDL_LoadBMP("graphics/boy/walking_sw02.bmp"));
    m_spriteDownLeft->load(SDL_LoadBMP("graphics/boy/walking_sw03.bmp"));
    m_spriteDownLeft->load(SDL_LoadBMP("graphics/boy/walking_sw04.bmp"));
    m_spriteDownLeft->load(SDL_LoadBMP("graphics/boy/walking_sw05.bmp"));
    m_spriteDownLeft->load(SDL_LoadBMP("graphics/boy/walking_sw06.bmp"));
    m_spriteDownLeft->load(SDL_LoadBMP("graphics/boy/walking_sw07.bmp"));

    m_currentSprite = m_spriteDown;

    m_width = 35;
    m_height = 50;

    srand(time(NULL));
}

Character::~Character() {
    delete m_currentSprite;
    delete m_spriteRight;
    delete m_spriteLeft;
    delete m_spriteUp;
    delete m_spriteDown;
    delete m_spriteUpRight;
    delete m_spriteUpLeft;
    delete m_spriteDownRight;
    delete m_spriteDownLeft;
}

SDL_Surface *Character::getCurrentSprite() {
    return m_currentSprite->getFrame(m_currentFrame);
}

int Character::getCharacterX() {
    return m_currentX;
}

int Character::getCharacterY() {
    return m_currentY;
}

int Character::getGraphicWidth() {
    return getCurrentSprite()->w;
}

int Character::getGraphicHeight() {
    return getCurrentSprite()->h;
}

void Character::tick() {
    if (m_currentX == m_destX && m_currentY == m_destY) {
       // generate new destination:
       m_destX = rand() % (m_mapWidth - m_width);
       m_destY = rand() % (m_mapHeight - m_height);

       //m_destX = m_mapWidth - m_width;
       //m_destY = 4;

       // slow us down:
       velocity = 0;
    }

    if (m_currentX < m_destX && m_currentY == m_destY)
       m_currentSprite = m_spriteRight;
    else if (m_currentX > m_destX && m_currentY == m_destY)
       m_currentSprite = m_spriteLeft;
    else if (m_currentX < m_destX && m_currentY < m_destY)
        m_currentSprite = m_spriteDownRight;
    else if (m_currentX > m_destX && m_currentY < m_destY)
        m_currentSprite = m_spriteDownLeft;
    else if (m_currentX < m_destX && m_currentY > m_destY)
        m_currentSprite = m_spriteUpRight;
    else if (m_currentX > m_destX && m_currentY > m_destY)
        m_currentSprite = m_spriteUpLeft;
    else if (m_currentX == m_destX && m_currentY > m_destY)
        m_currentSprite = m_spriteUp;
    else
        m_currentSprite = m_spriteDown;

    // update current frame:
    m_currentFrame = (m_currentFrame == m_currentSprite->getFrameCount() - 1) ? 0 : m_currentFrame + 1;

    if (velocity < 4) velocity++;


    // if we're close, set us to our goal:
    if (abs(m_currentX - m_destX) <= 4)
       m_currentX = m_destX;

    if (abs(m_currentY - m_destY) <= 4)
       m_currentY = m_destY;

    if (m_currentX < m_destX)
       m_currentX = m_currentX + velocity;
    else if (m_currentX > m_destX)
        m_currentX = m_currentX - velocity;

    if (m_currentY < m_destY)
       m_currentY = m_currentY + velocity;
    else if (m_currentY > m_destY)
       m_currentY = m_currentY - velocity;
}
