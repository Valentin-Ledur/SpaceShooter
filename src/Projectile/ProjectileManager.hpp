#ifndef __PROJECTILE_MANAGER__
#define __PROJECTILE_MANAGER__

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include "defines.hpp"
#include "Game/GameStatut.hpp"
#include "Animation/Animation.hpp"
#include "Projectile/Projectile.hpp"

class ProjectileManager
{
private:
    std::list<Projectile> player_projectile = std::list<Projectile>();
    SDL_Rect texture_rectangle = BASE_RECT;
    Animation projectile;

public:
    ProjectileManager() {};
    ~ProjectileManager() {};

    void Init(SDL_Renderer *_renderer);
    void HandleEvent(SDL_Event _event, SDL_Point _position, GameStatut _statut);
    void Update(int _width, int _height);
    void Display(SDL_Renderer *_renderer);
    void Reset();
    void Clean(){ projectile.Clean(); }
    std::list<Projectile> *GetPlayerProjectilePtr() { return &player_projectile; }
};

#endif