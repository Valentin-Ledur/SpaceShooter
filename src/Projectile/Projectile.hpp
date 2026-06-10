#ifndef __PROJECTILE__
#define __PROJECTILE__

#include <SDL2/SDL.h>

class Projectile
{
private:
    SDL_Point position = {0, 0};
    SDL_Point direction = {0, 0};

public:
    Projectile() {};
    Projectile(SDL_Point _position, SDL_Point _direction) : position(_position), direction(_direction) {};
    ~Projectile() {};

    SDL_Point *GetPosition() { return &position; }
    SDL_Point *GetDirection() { return &direction; }
};

#endif