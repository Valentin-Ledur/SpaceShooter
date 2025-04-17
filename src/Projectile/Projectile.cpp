#include <iostream>
#include <SDL2/SDL.h>
#include "Projectile/Projectile.hpp"

Projectile::Projectile(float _position_x, float _position_y, float _direction_x, float _direction_y){
    position_x = _position_x;
    position_y = _position_y;
    direction_x = _direction_x;
    direction_y = _direction_y;
}

bool Projectile::IsOutScreen(int width, int height){
    if(position_x < 0 || position_x > width || position_y < 0 || position_y > height)
		return true;
	return false;
}

void Projectile::CopyInRenderer(SDL_Texture *texture, SDL_Renderer *renderer){
    SDL_Rect position = {(int) position_x, (int) position_y, 5, 5};

    //Ajout de la texture au rendu.
    if(SDL_RenderCopy(renderer, texture, NULL, &position)){
        SDL_Log("Erreur: chargement de l'image du projectile dans le rendu : %s\n", SDL_GetError());
    }
}

void Projectile::Move(){
    position_x += direction_x*10;
    position_y += direction_y*10;
}

//Getters

float Projectile::GetPositionX(){
    return position_x;
}

float Projectile::GetPositionY(){
    return position_y;
}

float Projectile::GetDirectionX(){
    return direction_x;
}

float Projectile::GetDirectionY(){
    return direction_y;
}