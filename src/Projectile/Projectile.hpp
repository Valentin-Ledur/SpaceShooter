#ifndef __PROJECTILE__
#define __PROJECTILE__

#include <SDL2/SDL.h>

class Projectile
{
private:
    SDL_Point position = {0, 0};
    SDL_Point direction = {0, 0};
    double angle = 0.0;

public:
    Projectile() {};
    Projectile(SDL_Point _position, SDL_Point _direction, double _angle) : position(_position), direction(_direction), angle(_angle) {};
    ~Projectile() {};

    SDL_Point *GetPosition() { return &position; }
    SDL_Point *GetDirection() { return &direction; }
    double GetAngle() { return angle; }
};

#endif