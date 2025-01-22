#ifndef __PLAYER__
#define __PLAYER__

#include <list>
#include "../include/Projectile/Projectile.hpp"

class Player
{
private:
    float position_x;
    float position_y;
    double angle;
    std::list <Projectile> projectile_list;
    int hp;
    bool up;
    bool down;
    bool right;
    bool left;

    double getAngle(SDL_Event event);

public:
    Player();
    Player(int width, int height);
    void Move(int width, int height);
    bool IsHit(float _position_x, float _position_y);
    void CopyInRenderer(SDL_Texture *texture, SDL_Renderer *renderer);
    void HandleKey(SDL_Event event);
    void KeyRelease(SDL_Event event);
    void AddProjectile(Projectile _projectile);
    void Angle(SDL_Event event);
    void DecreaseHP(int value);

    //Getters

    int GetHP();
    float GetPositionX();
    float GetPositionY();
    std::list<Projectile> GetProjectileList();
    
    
};

#endif