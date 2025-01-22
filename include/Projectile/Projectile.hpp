#ifndef __PROJECTILE__
#define __PROJECTILE__

#include <../include/SDL2/SDL.h>

class Projectile
{
private:
    float position_x;
    float position_y;
    float direction_x;
    float direction_y;

public:
    Projectile(float _position_x, float _position_y, float _direction_x, float _direction_y);
    bool IsOutScreen(int width, int height);
    void Move();
    void CopyInRenderer(SDL_Texture *texture, SDL_Renderer *renderer);
    float GetPositionX();
    float GetPositionY();
    float GetDirectionX();
    float GetDirectionY();
};

#endif