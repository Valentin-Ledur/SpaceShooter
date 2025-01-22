#ifndef __ASTEROID__
#define __ASTEROID__

#include <../include/SDL2/SDL.h>

class Asteroid
{
private:
    int size;
    float position_x;
    float position_y;
    float direction_x;
    float direction_y;

public:
    Asteroid(int width, int height);
    Asteroid(int _size, float _position_x, float _position_y);
    void Move();
    bool IsHit(float _position_x, float _position_y);
    bool IsOutScreen(int width, int height);
    void CopyInRenderer(SDL_Texture *texture, SDL_Renderer *renderer);
    bool IsInside(float _position_x, float _position_y);

    //Getters

    float GetPositionX();
    float GetPositionY();
    int GetSize();
};

#endif