#include <list>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include "Utils/Utils.hpp"
#include "Game/GameStatut.hpp"
#include "defines.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerManager.hpp"

void PlayerManager::Init(int _hp, SDL_Point _position, SDL_Rect _texture_rectangle, std::string _texture_path, SDL_Renderer *_renderer)
{
    player = Player(_hp, _position);
    start_position = _position;
    texture_rectangle = _texture_rectangle;
    texture = Utils::CreateTexture(_renderer, _texture_path, _texture_rectangle);
}

void PlayerManager::MovePlayer(int _width, int _height)
{
    if (up && player.GetPosition()->y > texture_rectangle.h / 2)
        player.GetPosition()->y -= PLAYER_SPEED;

    if (down && player.GetPosition()->y < _height - texture_rectangle.h / 2)
        player.GetPosition()->y += PLAYER_SPEED;

    if (right && player.GetPosition()->x < _width - 63)
        player.GetPosition()->x += PLAYER_SPEED;

    if (left && player.GetPosition()->x > 63)
        player.GetPosition()->x -= PLAYER_SPEED;
}

void PlayerManager::HandleEvent(SDL_Event _event, GameStatut _statut)
{
    if (_statut == PLAY)
    {
        switch (_event.key.keysym.sym)
        {
        case SDLK_z:
        {
            if (_event.type == SDL_KEYDOWN)
                up = true;
            else if (_event.type == SDL_KEYUP)
                up = false;
        }
        break;
        case SDLK_q:
        {
            if (_event.type == SDL_KEYDOWN)
                left = true;
            else if (_event.type == SDL_KEYUP)
                left = false;
        }
        break;
        case SDLK_s:
        {
            if (_event.type == SDL_KEYDOWN)
                down = true;
            else if (_event.type == SDL_KEYUP)
                down = false;
        }
        break;
        case SDLK_d:
        {
            if (_event.type == SDL_KEYDOWN)
                right = true;
            else if (_event.type == SDL_KEYUP)
                right = false;
        }
        break;
        }
    }
}

void PlayerManager::Update(int _width, int _height)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point mouse_position = {x, y};
    SDL_Point *_position = player.GetPosition();
    rotation = atan2(_position->y - mouse_position.y, _position->x - mouse_position.x) * 180.0 / M_PI - 180;
    MovePlayer(_width, _height);
}

void PlayerManager::Display(SDL_Renderer *_renderer)
{
    SDL_Point *player_position = player.GetPosition();
    SDL_Rect position = {player_position->x - 63, player_position->y - 13, 125, 25};

    if (SDL_RenderCopyEx(_renderer, texture, NULL, &position, rotation, NULL, SDL_FLIP_NONE))
    {
        SDL_Log("Erreur: chargement de la texture du joueur dans le rendu : %s\n", SDL_GetError());
    }
}

void PlayerManager::Reset()
{
    *(player.GetHp()) = PLAYER_BASE_HP;
    *(player.GetPosition()) = start_position;
}
