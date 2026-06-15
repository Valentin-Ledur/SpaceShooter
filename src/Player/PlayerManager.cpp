#include <list>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include "Utils/Utils.hpp"
#include "Game/GameStatut.hpp"
#include "defines.hpp"
#include "Player/Player.hpp"
#include "Player/PlayerManager.hpp"

void PlayerManager::Init(int _hp, SDL_Point _position, SDL_Renderer *_renderer)
{
    player = Player(_hp, _position);
    start_position = _position;
    texture_rectangle = PLAYER_RECT_TEXTURE;

    idle_texture_1 = Utils::CreateTexture(_renderer, PLAYER_IDLE_1_TEXTURE_PATH, texture_rectangle);
    idle_texture_2 = Utils::CreateTexture(_renderer, PLAYER_IDLE_2_TEXTURE_PATH, texture_rectangle);
    idle_texture_3 = Utils::CreateTexture(_renderer, PLAYER_IDLE_3_TEXTURE_PATH, texture_rectangle);

    active_texture_1 = Utils::CreateTexture(_renderer, PLAYER_ACTIVE_1_TEXTURE_PATH, texture_rectangle);
    active_texture_2 = Utils::CreateTexture(_renderer, PLAYER_ACTIVE_2_TEXTURE_PATH, texture_rectangle);
}

bool PlayerManager::IsMoving()
{
    return (up || down || right || left);
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
    SDL_Rect position = {player_position->x - PLAYER_WIDTH / 2,
                         player_position->y - PLAYER_HEIGHT / 2,
                         PLAYER_WIDTH,
                         PLAYER_HEIGHT};

    if (IsMoving())
    {
        int frame = (SDL_GetTicks() / PLAYER_ANIMATION_SPEED) % PLAYER_ACTIVE_FRAME;

        switch (frame)
        {
        case 0:
            if (SDL_RenderCopyEx(_renderer, active_texture_1, NULL, &position, rotation, NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du joueur dans le rendu : %s\n", SDL_GetError());
            }
            break;
        case 1:
            if (SDL_RenderCopyEx(_renderer, active_texture_2, NULL, &position, rotation, NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du joueur dans le rendu : %s\n", SDL_GetError());
            }
            break;
        }
    }
    else
    {
        int frame = (SDL_GetTicks() / PLAYER_ANIMATION_SPEED) % PLAYER_IDLE_FRAME;

        switch (frame)
        {
        case 0:
            if (SDL_RenderCopyEx(_renderer, idle_texture_1, NULL, &position, rotation, NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du joueur dans le rendu : %s\n", SDL_GetError());
            }
            break;
        case 1:
            if (SDL_RenderCopyEx(_renderer, idle_texture_2, NULL, &position, rotation, NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du joueur dans le rendu : %s\n", SDL_GetError());
            }
            break;
        case 2:
            if (SDL_RenderCopyEx(_renderer, idle_texture_3, NULL, &position, rotation, NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du joueur dans le rendu : %s\n", SDL_GetError());
            }
            break;
        }
    }
}
void PlayerManager::Clean()
{
    SDL_DestroyTexture(idle_texture_1);
    SDL_DestroyTexture(idle_texture_2);
    SDL_DestroyTexture(idle_texture_3);

    SDL_DestroyTexture(active_texture_1);
    SDL_DestroyTexture(active_texture_2);
}

void PlayerManager::Reset()
{
    *(player.GetHp()) = PLAYER_BASE_HP;
    *(player.GetPosition()) = start_position;
}
