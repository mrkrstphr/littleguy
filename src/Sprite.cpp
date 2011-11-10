#include "Sprite.h"

Sprite::Sprite() {

}

Sprite::~Sprite() {

}

SDL_Surface *Sprite::getFrame(int frameNumber) {
    if (frameNumber < getFrameCount())
        return m_frames.at(frameNumber);
    else
        return NULL;

    // else -- throw exception
}

void Sprite::load(SDL_Surface* newFrame) {
    SDL_SetColorKey(newFrame, SDL_SRCCOLORKEY, SDL_MapRGB(newFrame->format, 255, 0, 255));
    m_frames.push_back(newFrame);
}

int Sprite::getFrameCount() {
    return m_frames.size();
}
