#include <string>
#include <SDL2/SDL.h>
#include "Utils/Utils.hpp"
#include "UI/Button/Button.hpp"
#include "Game/GameStatut.hpp"

Button::Button(int _x, int _y, int _w, int _h, SDL_Color _base_color, SDL_Color _active_color, std::string _text, int _font_size, GameStatut _action)
{
    position = {_x, _y, _w, _h};
    base_color = _base_color;
    active_color = _active_color;
    current_color = base_color;
    text = _text;
    font_size = _font_size;
    action = _action;
}

bool Button::IsInside(int x, int y)
{
    SDL_Point p = {x, y};
    if (SDL_PointInRect(&p, &position))
    {
        current_color = active_color;
        return true;
    }
    else
    {
        current_color = base_color;
        return false;
    }
}

void Button::CopyInRenderer(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, current_color.r, current_color.g, current_color.b, current_color.a);
    SDL_RenderFillRect(renderer, &position);
    SDL_Color white = {255, 255, 255, 255};
    Utils::AddTextToRenderer(renderer, text.data(), font_size, position, NULL, white);
}

GameStatut Button::GetAction()
{
    return action;
}