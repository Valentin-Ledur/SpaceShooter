#include <list>
#include <string>
#include "Utils/Utils.hpp"
#include "defines.hpp"
#include "Enemy/Asteroid/Asteroid.hpp"
#include "Enemy/Asteroid/AsteroidType.hpp"
#include "Enemy/EnemyManager.hpp"

void EnemyManager::Init(SDL_Renderer *_renderer)
{
    texture_rectangle_50 = ASTEROID_RECT_50;
    texture_rectangle_100 = ASTEROID_RECT_100;
    texture_rectangle_150 = ASTEROID_RECT_150;

    // Basic
    texture_basic_base_1_100 = Utils::CreateTexture(_renderer, ASTEROID_BASIC_BASE_1_TEXTURE_PATH, texture_rectangle_100);
    texture_basic_base_1_150 = Utils::CreateTexture(_renderer, ASTEROID_BASIC_BASE_1_TEXTURE_PATH, texture_rectangle_150);

    texture_basic_base_2_100 = Utils::CreateTexture(_renderer, ASTEROID_BASIC_BASE_2_TEXTURE_PATH, texture_rectangle_100);
    texture_basic_base_2_150 = Utils::CreateTexture(_renderer, ASTEROID_BASIC_BASE_2_TEXTURE_PATH, texture_rectangle_150);

    texture_basic_1_50 = Utils::CreateTexture(_renderer, ASTEROID_BASIC_1_TEXTURE_PATH, texture_rectangle_50);
    texture_basic_2_50 = Utils::CreateTexture(_renderer, ASTEROID_BASIC_2_TEXTURE_PATH, texture_rectangle_50);
    texture_basic_3_50 = Utils::CreateTexture(_renderer, ASTEROID_BASIC_3_TEXTURE_PATH, texture_rectangle_50);
    texture_basic_4_50 = Utils::CreateTexture(_renderer, ASTEROID_BASIC_4_TEXTURE_PATH, texture_rectangle_50);

    // Brown
    texture_brown_base_1_100 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_BASE_1_TEXTURE_PATH, texture_rectangle_100);
    texture_brown_base_1_150 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_BASE_1_TEXTURE_PATH, texture_rectangle_150);

    texture_brown_base_2_100 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_BASE_2_TEXTURE_PATH, texture_rectangle_100);
    texture_brown_base_2_150 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_BASE_2_TEXTURE_PATH, texture_rectangle_150);

    texture_brown_1_50 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_1_TEXTURE_PATH, texture_rectangle_50);
    texture_brown_2_50 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_2_TEXTURE_PATH, texture_rectangle_50);
    texture_brown_3_50 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_3_TEXTURE_PATH, texture_rectangle_50);
    texture_brown_4_50 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_4_TEXTURE_PATH, texture_rectangle_50);

    // Ice
    texture_ice_base_1_100 = Utils::CreateTexture(_renderer, ASTEROID_ICE_BASE_1_TEXTURE_PATH, texture_rectangle_100);
    texture_ice_base_1_150 = Utils::CreateTexture(_renderer, ASTEROID_ICE_BASE_1_TEXTURE_PATH, texture_rectangle_150);

    texture_ice_base_2_100 = Utils::CreateTexture(_renderer, ASTEROID_ICE_BASE_2_TEXTURE_PATH, texture_rectangle_100);
    texture_ice_base_2_150 = Utils::CreateTexture(_renderer, ASTEROID_ICE_BASE_2_TEXTURE_PATH, texture_rectangle_150);

    texture_ice_1_50 = Utils::CreateTexture(_renderer, ASTEROID_ICE_1_TEXTURE_PATH, texture_rectangle_50);
    texture_ice_2_50 = Utils::CreateTexture(_renderer, ASTEROID_ICE_2_TEXTURE_PATH, texture_rectangle_50);
    texture_ice_3_50 = Utils::CreateTexture(_renderer, ASTEROID_ICE_3_TEXTURE_PATH, texture_rectangle_50);
    texture_ice_4_50 = Utils::CreateTexture(_renderer, ASTEROID_ICE_4_TEXTURE_PATH, texture_rectangle_50);
}

void EnemyManager::Clean()
{
    // Basic
    SDL_DestroyTexture(texture_basic_base_1_100);
    SDL_DestroyTexture(texture_basic_base_1_150);

    SDL_DestroyTexture(texture_basic_base_2_100);
    SDL_DestroyTexture(texture_basic_base_2_150);

    SDL_DestroyTexture(texture_basic_1_50);
    SDL_DestroyTexture(texture_basic_2_50);
    SDL_DestroyTexture(texture_basic_3_50);
    SDL_DestroyTexture(texture_basic_4_50);

    // Brown
    SDL_DestroyTexture(texture_brown_base_1_100);
    SDL_DestroyTexture(texture_brown_base_1_150);

    SDL_DestroyTexture(texture_brown_base_2_100);
    SDL_DestroyTexture(texture_brown_base_2_150);

    SDL_DestroyTexture(texture_brown_1_50);
    SDL_DestroyTexture(texture_brown_2_50);
    SDL_DestroyTexture(texture_brown_3_50);
    SDL_DestroyTexture(texture_brown_4_50);

    // Ice
    SDL_DestroyTexture(texture_ice_base_1_100);
    SDL_DestroyTexture(texture_ice_base_1_150);

    SDL_DestroyTexture(texture_ice_base_2_100);
    SDL_DestroyTexture(texture_ice_base_2_150);

    SDL_DestroyTexture(texture_ice_1_50);
    SDL_DestroyTexture(texture_ice_2_50);
    SDL_DestroyTexture(texture_ice_3_50);
    SDL_DestroyTexture(texture_ice_4_50);
}

void EnemyManager::Update(int _width, int _height)
{
    for (auto a = asteroid_list.begin(); a != asteroid_list.end();)
    {
        a->Move();

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

void EnemyManager::DisplayBaseAsteroid(Asteroid _a, SDL_Renderer *_renderer, AsteroidType _type)
{
    SDL_Rect position = {_a.GetPosition()->x - 25 * _a.GetSize(), _a.GetPosition()->y - 25 * _a.GetSize(), 50 * _a.GetSize(), 50 * _a.GetSize()};

    if (_a.GetSize() == 3)
    {
        switch (_type)
        {
        case BASIC:
            if (SDL_RenderCopyEx(_renderer, texture_basic_base_1_150, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        case BROWN:
            if (SDL_RenderCopyEx(_renderer, texture_brown_base_1_150, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        default:
            if (SDL_RenderCopyEx(_renderer, texture_ice_base_1_150, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;
        }
    }
    else
    {
        switch (_type)
        {
        case BASIC:
            if (SDL_RenderCopyEx(_renderer, texture_basic_base_1_100, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        case BROWN:
            if (SDL_RenderCopyEx(_renderer, texture_brown_base_1_100, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        default:
            if (SDL_RenderCopyEx(_renderer, texture_ice_base_1_100, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;
        }
    }
}

void EnemyManager::DisplayAsteroidWithTrail(Asteroid _a, SDL_Renderer *_renderer, AsteroidType _type)
{
    int frame = (SDL_GetTicks() / ASTEROID_ANIMATION_SPEED) % ASTEROID_BASIC_FRAME;
    SDL_Rect position = {_a.GetPosition()->x - 25 * _a.GetSize(), _a.GetPosition()->y - 25 * _a.GetSize(), 50 * _a.GetSize(), 50 * _a.GetSize()};

    switch (frame)
    {
    case 0:
        switch (_type)
        {
        case BASIC_TRAIL:
            if (SDL_RenderCopyEx(_renderer, texture_basic_1_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        case BROWN_TRAIL:
            if (SDL_RenderCopyEx(_renderer, texture_brown_1_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        default:
            if (SDL_RenderCopyEx(_renderer, texture_ice_1_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;
        }
        break;
    case 1:
        switch (_type)
        {
        case BASIC_TRAIL:
            if (SDL_RenderCopyEx(_renderer, texture_basic_2_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        case BROWN_TRAIL:
            if (SDL_RenderCopyEx(_renderer, texture_brown_2_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        default:
            if (SDL_RenderCopyEx(_renderer, texture_ice_2_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;
        }
        break;
    case 2:
        switch (_type)
        {
        case BASIC_TRAIL:
            if (SDL_RenderCopyEx(_renderer, texture_basic_3_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        case BROWN_TRAIL:
            if (SDL_RenderCopyEx(_renderer, texture_brown_3_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        default:
            if (SDL_RenderCopyEx(_renderer, texture_ice_3_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;
        }
        break;
    default:
        switch (_type)
        {
        case BASIC_TRAIL:
            if (SDL_RenderCopyEx(_renderer, texture_basic_4_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

        case BROWN_TRAIL:
            if (SDL_RenderCopyEx(_renderer, texture_brown_4_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;

       default:
            if (SDL_RenderCopyEx(_renderer, texture_ice_4_50, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
            {
                SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
            }
            break;
        }
        break;
    }
}

void EnemyManager::Display(SDL_Renderer *_renderer)
{
    for (auto a : asteroid_list)
    {
        SDL_Rect position = {a.GetPosition()->x - 25 * a.GetSize(), a.GetPosition()->y - 25 * a.GetSize(), 50 * a.GetSize(), 50 * a.GetSize()};

        if (a.GetType() == BASIC || a.GetType() == BROWN || a.GetType() == ICE)
        {
            DisplayBaseAsteroid(a, _renderer, a.GetType());
        }
        else
        {
            DisplayAsteroidWithTrail(a, _renderer, a.GetType());
        }
    }
}

void EnemyManager::Reset()
{
    // A changer
    addNewAsteroid = (int) SDL_GetTicks();
    addMore = 1000;
    timeNew = 500;
    asteroid_list.clear();
}