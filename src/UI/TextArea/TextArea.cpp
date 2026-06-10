#include <string>
#include <SDL2/SDL.h>
#include "Utils/Utils.hpp"
#include "UI/TextArea/TextArea.hpp"

TextArea::TextArea(int _x, int _y, int _w, int _h, SDL_Color _color, std::string _text, int _font_size)
{
    position = {_x, _y, _w, _h};
    color = _color;
    text = _text;
    font_size = _font_size;
}

TextArea::TextArea(int _x, int _y, int _w, int _h, SDL_Color _color, int *_text, int _font_size)
{
    position = {_x, _y, _w, _h};
    color = _color;
    value = _text;
    font_size = _font_size;
}

void TextArea::CopyInRenderer(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &position);
    SDL_Color white = {255, 255, 255, 255};
    if (value == NULL)
    {
        Utils::AddTextToRenderer(renderer, text.data(), font_size, position, NULL, white);
    }
    else
    {
        std::string new_text = std::to_string(*value);
        Utils::AddTextToRenderer(renderer, new_text.data(), font_size, position, NULL, white);
    }
}
