#ifndef __ASTEROID__
#define __ASTEROID__

#include <SDL2/SDL.h>
#include "Enemy/Asteroid/AsteroidType.hpp"

class Asteroid
{
private:
    int size = 0;
    double angle = 0.0;
    int rotation_speed = 0;
    AsteroidType type = BASIC;
    bool trail = false;
    SDL_Point position = {0, 0};
    SDL_Point direction = {0, 0};

public:
    Asteroid() {};
    Asteroid(int _width, int _height);
    Asteroid(int _size, SDL_Point _position, AsteroidType _type);
    ~Asteroid() {};

    void Move();
    int GetSize() { return size; }
    AsteroidType GetType() { return type; }
    double GetAngle() { return angle; }
    SDL_Point *GetPosition() { return &position; }
    SDL_Point *GetDirection() { return &direction; }
};

#endif