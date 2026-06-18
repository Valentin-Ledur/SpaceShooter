#include <list>
#include <string>
#include <SDL2/SDL.h>
#include "Utils/Utils.hpp"
#include "defines.hpp"
#include "Game/GameStatut.hpp"
#include "Projectile/Projectile.hpp"
#include "Projectile/ProjectileManager.hpp"

void ProjectileManager::Init(SDL_Renderer *_renderer)
{
    texture_rectangle = PROJECTILE_RECT_TEXTURE;
    projectile = Animation({PROJECTILE_1_TEXTURE_PATH, PROJECTILE_2_TEXTURE_PATH, PROJECTILE_3_TEXTURE_PATH},
                           PROJECTILE_ANIMATION_SPEED,
                           texture_rectangle,
                           _renderer);
}

void ProjectileManager::HandleEvent(SDL_Event _event, SDL_Point _position, GameStatut _statut)
{
    if (_statut == PLAY)
    {
        if (_event.type == SDL_MOUSEBUTTONDOWN)
        {
            float dir_x = _event.button.x - _position.x;
            float dir_y = _event.button.y - _position.y;

            float norme = sqrtf(dir_x * dir_x + dir_y * dir_y);

            SDL_Point projectile_direction = {0, 0};

            if (norme != 0)
            {
                projectile_direction.x = (dir_x / norme) * PROJECTILE_SPEED;
                projectile_direction.y = (dir_y / norme) * PROJECTILE_SPEED;
            }

            double angle = atan2(dir_y, dir_x) * 180.0 / M_PI;

            player_projectile.push_back(Projectile(_position, projectile_direction, angle));
        }
    }
}

void ProjectileManager::Update(int _width, int _height)
{
    for (auto p = player_projectile.begin(); p != player_projectile.end();)
    {
        p->GetPosition()->x += p->GetDirection()->x;
        p->GetPosition()->y += p->GetDirection()->y;

        if (Utils::IsOutScreen(_width, _height, *p->GetPosition()))
        {
            p = player_projectile.erase(p);
        }
        else
        {
            ++p;
        }
    }
}

void ProjectileManager::Display(SDL_Renderer *_renderer)
{
    for (auto p : player_projectile)
    {
        projectile.DisplayWithRotation(_renderer, *(p.GetPosition()), p.GetAngle());
    }
}

void ProjectileManager::Reset()
{
    player_projectile.clear();
}