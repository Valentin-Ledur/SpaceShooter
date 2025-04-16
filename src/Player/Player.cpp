#include <list>
#include <cmath>
#include "../include/Player/Player.hpp"
#include <include/SDL2/SDL.h>
#include <include/SDL2/SDL_image.h>
#include "../include/Projectile/Projectile.hpp"

double Player::getAngle(SDL_Event event){
    return 0.0;
}

Player::Player(){
    
}

Player::Player(int width, int height){
    angle = 0;
    position_x = width/2.f;
    position_y = height/2.f;
    hp = 3;
    up = false;
    down = false;
    right = false;
    left = false;
    
}

void Player::Move(int width, int height){
    if (up && position_y > 13)
        position_y -= 5;
    if (down && position_y < height - 13)
        position_y += 5;
    if (right && position_x < width - 63)
        position_x += 5;
    if (left && position_x > 63)
        position_x -= 5;
}

bool Player::IsHit(float _position_x, float _position_y){
    if ((_position_x >= position_x-63 && _position_x <= position_x+63) && (_position_y >= position_y-13 && _position_y <= position_y+13)){
        return true;
    }
    return false;
}

void Player::CopyInRenderer(SDL_Texture *texture, SDL_Renderer *renderer){
    SDL_Rect position = {(int) position_x-63, (int) position_y-13, 125, 25};
    //Ajout de la texture au rendu.
    if(SDL_RenderCopyEx(renderer, texture, NULL, &position, angle, NULL, SDL_FLIP_NONE)){
        SDL_Log("Erreur: chargement de l'image du joueur dans le rendu : %s\n", SDL_GetError());
    }
}

void Player::HandleKey(SDL_Event event){
    switch (event.key.keysym.sym)
    {
    case SDLK_z:
        up = true;
        break;
    case SDLK_q:
        left = true;
        break;
    case SDLK_s:
        down = true;
        break;
    case SDLK_d:
        right = true;
        break;
    }
}

void Player::KeyRelease(SDL_Event event){
    switch (event.key.keysym.sym)
    {
    case SDLK_z:
        up = false;
        break;
    case SDLK_q:
        left = false;
        break;
    case SDLK_s:
        down = false;
        break;
    case SDLK_d:
        right = false;
        break;
    }
}

void Player::AddProjectile(Projectile _projectile){
    projectile_list.push_back(_projectile);
}

void Player::Angle(SDL_Event event){
    angle =  atan2(position_y - event.button.y, position_x - event.button.x) * 180.0 / M_PI - 180;
}

void Player::DecreaseHP(int value){
    hp -= value;
}

//Getters

int Player::GetHP(){
    return hp;
}

float Player::GetPositionX(){
    return position_x;
}

float Player::GetPositionY(){
    return position_y;
}

std::list<Projectile> Player::GetProjectileList(){
    return projectile_list;
}