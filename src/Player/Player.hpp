#ifndef __PLAYER__
#define __PLAYER__

#include <SDL2/SDL.h>
#include "Projectile/Projectile.hpp"

class Player
{
private:
    int hp = 0;
    SDL_Point position = {0, 0};

public:
    Player() {};
    Player(int _hp, SDL_Point _position) : hp(_hp), position(_position) {};
    ~Player() {};

    int *GetHp() { return &hp; }
    SDL_Point *GetPosition() { return &position; }
};

#endif