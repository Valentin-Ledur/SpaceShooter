#ifndef __UI_BUTTON__
#define __UI_BUTTON__

#include <string>
#include <SDL2/SDL.h>
#include "Utils/Utils.hpp"
#include "Game/GameStatut.hpp"

class Button
{
private:
    SDL_Rect position;
    SDL_Color current_color;
    SDL_Color base_color;
    SDL_Color active_color;
    std::string text;
    int font_size;
    GameStatut action;

public:
    Button(int _x, int _y, int _w, int _h, SDL_Color _base_color, SDL_Color _active_color, std::string _text, int _font_size, GameStatut _action);
    ~Button(){};

    bool IsInside(int x, int y);

    void CopyInRenderer(SDL_Renderer *renderer);
    GameStatut GetAction();
};
#endif