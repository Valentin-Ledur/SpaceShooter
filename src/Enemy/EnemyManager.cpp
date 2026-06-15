#include <list>
#include <string>
#include "Utils/Utils.hpp"
#include "defines.hpp"
#include "Enemy/Asteroid/Asteroid.hpp"
#include "Enemy/EnemyManager.hpp"

void EnemyManager::Init(SDL_Renderer *_renderer)
{
    texture_rectangle_50 = _texture_50_rectangle;
    texture_rectangle_100 = _texture_100_rectangle;
    texture_rectangle_150 = _texture_150_rectangle;

    texture_50 = Utils::CreateTexture(_renderer, _texture_50_path, _texture_50_rectangle);
    texture_100 = Utils::CreateTexture(_renderer, _texture_100_path, _texture_100_rectangle);
    texture_150 = Utils::CreateTexture(_renderer, _texture_150_path, _texture_150_rectangle);
}

void EnemyManager::Clean()
{
    SDL_DestroyTexture(texture_50);
    SDL_DestroyTexture(texture_100);
    SDL_DestroyTexture(texture_150);
}

void EnemyManager::Update(int _width, int _height)
{
    for (auto a = asteroid_list.begin(); a != asteroid_list.end();)
    {
        a->GetPosition()->x += a->GetDirection()->x;
        a->GetPosition()->y += a->GetDirection()->y;

        if (Utils::IsOutScreen(_width, _height, *a->GetPosition()))
        {
            a = asteroid_list.erase(a);
        }
        else
        {
            ++a;
        }
    }

    if (addNewAsteroid < SDL_GetTicks())
    {
        asteroid_list.push_back(Asteroid(_width, _height));
        addNewAsteroid += timeNew;
    }
    if (addMore < SDL_GetTicks() && timeNew > 100)
    {
        timeNew -= 50;
        addMore += 1000;
    }
}

void EnemyManager::Display(SDL_Renderer *_renderer)
{
    for (auto a : asteroid_list)
    {
        SDL_Rect position = {a.GetPosition()->x - 25 * a.GetSize(), a.GetPosition()->y - 25 * a.GetSize(), 50 * a.GetSize(), 50 * a.GetSize()};
        switch (a.GetSize())
        {
        case 1:
            if (SDL_RenderCopy(_renderer, texture_50, NULL, &position))
            {
                SDL_Log("Erreur: chargement de l'image de l'Asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;
        case 2:
            if (SDL_RenderCopy(_renderer, texture_100, NULL, &position))
            {
                SDL_Log("Erreur: chargement de l'image de l'Asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;
        case 3:
            if (SDL_RenderCopy(_renderer, texture_150, NULL, &position))
            {
                SDL_Log("Erreur: chargement de l'image de l'Asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;
        }
    }
}

void EnemyManager::Reset()
{
    // A changer
    addNewAsteroid = 0;
    addMore = 1000;
    timeNew = 500;
    asteroid_list.clear();
}