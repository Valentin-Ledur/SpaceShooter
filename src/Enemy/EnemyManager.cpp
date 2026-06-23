#include <list>
#include <string>
#include "Utils/Utils.hpp"
#include "defines.hpp"
#include "Animation/Animation.hpp"
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

    basic_trail = Animation({ASTEROID_BASIC_1_TEXTURE_PATH, ASTEROID_BASIC_2_TEXTURE_PATH, ASTEROID_BASIC_3_TEXTURE_PATH, ASTEROID_BASIC_4_TEXTURE_PATH},
                            ASTEROID_ANIMATION_SPEED,
                            texture_rectangle_50,
                            _renderer);

    // Brown
    texture_brown_base_1_100 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_BASE_1_TEXTURE_PATH, texture_rectangle_100);
    texture_brown_base_1_150 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_BASE_1_TEXTURE_PATH, texture_rectangle_150);

    texture_brown_base_2_100 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_BASE_2_TEXTURE_PATH, texture_rectangle_100);
    texture_brown_base_2_150 = Utils::CreateTexture(_renderer, ASTEROID_BROWN_BASE_2_TEXTURE_PATH, texture_rectangle_150);

    brown_trail = Animation({ASTEROID_BROWN_1_TEXTURE_PATH, ASTEROID_BROWN_2_TEXTURE_PATH, ASTEROID_BROWN_3_TEXTURE_PATH, ASTEROID_BROWN_4_TEXTURE_PATH},
                            ASTEROID_ANIMATION_SPEED,
                            texture_rectangle_50,
                            _renderer);

    // Ice
    texture_ice_base_1_100 = Utils::CreateTexture(_renderer, ASTEROID_ICE_BASE_1_TEXTURE_PATH, texture_rectangle_100);
    texture_ice_base_1_150 = Utils::CreateTexture(_renderer, ASTEROID_ICE_BASE_1_TEXTURE_PATH, texture_rectangle_150);

    texture_ice_base_2_100 = Utils::CreateTexture(_renderer, ASTEROID_ICE_BASE_2_TEXTURE_PATH, texture_rectangle_100);
    texture_ice_base_2_150 = Utils::CreateTexture(_renderer, ASTEROID_ICE_BASE_2_TEXTURE_PATH, texture_rectangle_150);

    ice_trail = Animation({ASTEROID_ICE_1_TEXTURE_PATH, ASTEROID_ICE_2_TEXTURE_PATH, ASTEROID_ICE_3_TEXTURE_PATH, ASTEROID_ICE_4_TEXTURE_PATH},
                          ASTEROID_ANIMATION_SPEED,
                          texture_rectangle_50,
                          _renderer);
}

void EnemyManager::Clean()
{
    // Basic
    basic_trail.Clean();

    SDL_DestroyTexture(texture_basic_base_1_100);
    SDL_DestroyTexture(texture_basic_base_1_150);

    SDL_DestroyTexture(texture_basic_base_2_100);
    SDL_DestroyTexture(texture_basic_base_2_150);

    // Brown
    brown_trail.Clean();

    SDL_DestroyTexture(texture_brown_base_1_100);
    SDL_DestroyTexture(texture_brown_base_1_150);

    SDL_DestroyTexture(texture_brown_base_2_100);
    SDL_DestroyTexture(texture_brown_base_2_150);

    // Ice
    ice_trail.Clean();

    SDL_DestroyTexture(texture_ice_base_1_100);
    SDL_DestroyTexture(texture_ice_base_1_150);

    SDL_DestroyTexture(texture_ice_base_2_100);
    SDL_DestroyTexture(texture_ice_base_2_150);
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
            if (*(_a.GetHP()) == 1)
            {
                if (SDL_RenderCopyEx(_renderer, texture_brown_base_1_150, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
                {
                    SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
                }
            }
            else
            {
                if (SDL_RenderCopyEx(_renderer, texture_brown_base_2_150, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
                {
                    SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
                }
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
            if (*(_a.GetHP()) == 1)
            {
                if (SDL_RenderCopyEx(_renderer, texture_brown_base_1_100, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
                {
                    SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
                }
            }
            else
            {
                if (SDL_RenderCopyEx(_renderer, texture_brown_base_2_100, NULL, &position, _a.GetAngle(), NULL, SDL_FLIP_NONE))
                {
                    SDL_Log("Erreur: chargement de la texture du asteroid dans le rendu : %s\n", SDL_GetError());
                }
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

    switch (_type)
    {
    case BASIC_TRAIL:
        basic_trail.DisplayWithRotation(_renderer, *(_a.GetPosition()), _a.GetAngle());
        break;

    case BROWN_TRAIL:
        brown_trail.DisplayWithRotation(_renderer, *(_a.GetPosition()), _a.GetAngle());
        break;

    default:
        ice_trail.DisplayWithRotation(_renderer, *(_a.GetPosition()), _a.GetAngle());
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

bool EnemyManager::AddAsteroid(Asteroid* _a)
{
    int* hp = _a->GetHP();
    if (_a->GetSize() > 1 && *hp - 1 <= 0)
    {
        asteroid_list.emplace_back(Asteroid(_a->GetSize(), *(_a->GetPosition()), _a->GetType()));
        asteroid_list.emplace_back(Asteroid(_a->GetSize(), *(_a->GetPosition()), _a->GetType()));
        return true;
    }
    else if(_a->GetSize() == 1)
    {
        return true;
    }
    else
    {
        *hp -= 1;
    }

    return false;
}

void EnemyManager::Reset()
{
    // A changer
    addNewAsteroid = (int)SDL_GetTicks();
    addMore = 1000;
    timeNew = 500;
    asteroid_list.clear();
}