#ifndef __UTILS__
#define __UTILS__

#include <iostream>
#include <SDL2/SDL.h>

namespace Utils
{
    void AddTextToRenderer(SDL_Renderer *renderer, const char *text, int fontSize, SDL_Rect textArea, const char *fontPath, SDL_Color color);
    SDL_Texture *CreateTexture(SDL_Renderer *renderer, std::string imagePath, SDL_Rect &rect);
};

#endif