#include <vector>
#include <SDL2/SDL.h>
#include "Utils/Utils.hpp"
#include "defines.hpp"
#include "Animation/Animation.hpp"

Animation::Animation(std::vector<std::string> _textures_path, int _timer, SDL_Rect _textures_rect, SDL_Renderer *_renderer)
{
    width = _textures_rect.w;
    height = _textures_rect.h;
    timer = _timer;

    for (auto &s : _textures_path)
    {
        texture_vector.push_back(Utils::CreateTexture(_renderer, s, _textures_rect));
    }
}

void Animation::Display(SDL_Renderer *_renderer, SDL_Point _position)
{
    int frame = (SDL_GetTicks() / timer) % texture_vector.size();
    SDL_Rect position = {_position.x - width / 2, _position.y - height / 2, width, height};

    if (SDL_RenderCopy(_renderer, texture_vector[frame], NULL, &position))
    {
        SDL_Log("Erreur: chargement de la texture dans le rendu : %s\n", SDL_GetError());
    }
}

void Animation::DisplayWithRotation(SDL_Renderer *_renderer, SDL_Point _position, double _angle)
{
    int frame = (SDL_GetTicks() / timer) % texture_vector.size();
    SDL_Rect position = {_position.x - width / 2, _position.y - height / 2, width, height};

    if (SDL_RenderCopyEx(_renderer, texture_vector[frame], NULL, &position, _angle, NULL, SDL_FLIP_NONE))
    {
        SDL_Log("Erreur: chargement de la texture avec rotation dans le rendu : %s\n", SDL_GetError());
    }
}

void Animation::Clean()
{
    for (std::vector<SDL_Texture *>::iterator it = texture_vector.begin(); it != texture_vector.end(); it++)
    {
        SDL_DestroyTexture(*it);
    }
}