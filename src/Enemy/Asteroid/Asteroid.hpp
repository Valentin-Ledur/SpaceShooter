#ifndef __ASTEROID__
#define __ASTEROID__

#include <SDL2/SDL.h>

class Asteroid
{
private:
    int size = 0;
    SDL_Point position = {0, 0};
    SDL_Point direction = {0, 0};

public:
    Asteroid() {};
    Asteroid(int _width, int _height);
    Asteroid(int _size, SDL_Point _position);
    ~Asteroid() {};

    int GetSize() { return size; }
    SDL_Point *GetPosition() { return &position; }
    SDL_Point *GetDirection() { return &direction; }
};

#endif