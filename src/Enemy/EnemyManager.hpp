#ifndef __ASTEROID_MANAGER__
#define __ASTEROID_MANAGER__

#include <list>
#include <string>
#include "Utils/Utils.hpp"
#include "defines.hpp"
#include "Animation/Animation.hpp"
#include "Enemy/Asteroid/Asteroid.hpp"

class EnemyManager
{
private:
    std::list<Asteroid> asteroid_list = std::list<Asteroid>();
    SDL_Rect texture_rectangle_50 = BASE_RECT;
    SDL_Rect texture_rectangle_100 = BASE_RECT;
    SDL_Rect texture_rectangle_150 = BASE_RECT;

    // Basic
    SDL_Texture *texture_basic_base_1_100 = NULL;
    SDL_Texture *texture_basic_base_1_150 = NULL;

    SDL_Texture *texture_basic_base_2_100 = NULL;
    SDL_Texture *texture_basic_base_2_150 = NULL;

    Animation basic_trail;

    // Brown

    SDL_Texture *texture_brown_base_1_100 = NULL;
    SDL_Texture *texture_brown_base_1_150 = NULL;

    SDL_Texture *texture_brown_base_2_100 = NULL;
    SDL_Texture *texture_brown_base_2_150 = NULL;
    
    Animation brown_trail;

    // Ice

    SDL_Texture *texture_ice_base_1_100 = NULL;
    SDL_Texture *texture_ice_base_1_150 = NULL;

    SDL_Texture *texture_ice_base_2_100 = NULL;
    SDL_Texture *texture_ice_base_2_150 = NULL;

    Animation ice_trail;

    // A changer
    int addNewAsteroid = 0;
    int addMore = 1000;
    int timeNew = 500;

    void DisplayBaseAsteroid(Asteroid _a, SDL_Renderer *_renderer, AsteroidType _type);
    void DisplayAsteroidWithTrail(Asteroid _a, SDL_Renderer *_renderer, AsteroidType _type);

public:
    EnemyManager() {};
    ~EnemyManager() {};

    void Init(SDL_Renderer *_renderer);
    void Update(int _width, int _height);
    void Display(SDL_Renderer *_renderer);
    void Reset();
    void Clean();
    std::list<Asteroid> *GetAsteroidListPtr() { return &asteroid_list; }
};

#endif