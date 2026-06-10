#ifndef __UTILS__
#define __UTILS__

#include <iostream>
#include <SDL2/SDL.h>

namespace Utils
{
    void AddTextToRenderer(SDL_Renderer *renderer, const char *text, int fontSize, SDL_Rect textArea, const char *fontPath, SDL_Color color);
    SDL_Texture *CreateTexture(SDL_Renderer *renderer, std::string imagePath, SDL_Rect &rect);
    // Genere un nombre aleatoire compris dans [range_min, range_max[.
    int Random(int range_min, int range_max);
    bool IsOutScreen(int width, int height, SDL_Point point);

};

#endif