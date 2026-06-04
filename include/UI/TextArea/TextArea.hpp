#ifndef __TEXT_AREA__
#define __TEXT_AREA__

#include <string>
#include <SDL2/SDL.h>
#include "Utils/Utils.hpp"

class TextArea
{
private:
    SDL_Rect position;
    SDL_Color color;
    std::string text;
    int font_size;

public:
    TextArea(int _x, int _y, int _w, int _h, SDL_Color _color, std::string _text, int _font_size);
    ~TextArea() {};

    void CopyInRenderer(SDL_Renderer *renderer);
};

#endif