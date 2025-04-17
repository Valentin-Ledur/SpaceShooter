#include <iostream>
#include "Enemy/Asteroid.hpp"
#include "Game/Game.hpp"

Asteroid::Asteroid(int width, int height){
    
    int initPos = Game::Random(1, 5);
    size = Game::Random(1, 4);

    if (initPos == 1) {                                        //gauche
      position_x = 0;
      position_y = Game::Random(0, 10);
      direction_x = Game::Random(1, 10);
      direction_y = Game::Random(-10, 10);
    } 
    else if (initPos == 2) {                                   //droit
      position_x = width;
      position_y = Game::Random(0, height);
      direction_x = -Game::Random(1, 10);
      direction_y = Game::Random(-10, 10);
    } 
    else if (initPos == 3) {                                   //haut
      position_x = Game::Random(0, width);
      position_y = 0;
      direction_x = Game::Random(-10, 10);
      direction_y = Game::Random(1, 10);
    } 
    else if (initPos == 4) {                                   //bas
      position_x = Game::Random(0, width);
      position_y = height;
      direction_x = Game::Random(-10, 10);
      direction_y = -Game::Random(1, 10);
    }else{
        std::cout << "erreur random incorrect" << std::endl;
    }
}

/*------------------------------------------------------------------------------------------------------*/

Asteroid::Asteroid(int _size, float _position_x, float _position_y){
    size = _size-1;
    position_x = _position_x;
    position_y = _position_y;
    direction_x = Game::Random(-10, 10);
    direction_y = Game::Random(-10, 10);
}

/*------------------------------------------------------------------------------------------------------*/

void Asteroid::Move(){
    position_x += direction_x;
    position_y += direction_y;
}

/*------------------------------------------------------------------------------------------------------*/

//Renvoit 1 si l'asteroid est touché par la position donné en parametre.
bool Asteroid::IsHit(float _position_x, float _position_y){
    if ((_position_x >= position_x-(size/2) && _position_x <= position_x+(size/2)) && (_position_y >= position_y-(size/2) && _position_y <= position_y+(size/2)))
        return true;
    return false;
}

/*------------------------------------------------------------------------------------------------------*/

//Renvoit 1 si l'asteroid est en dehors de l'ecran.
bool Asteroid::IsOutScreen(int width, int height){
	if(position_x < 0 || position_x > width || position_y < 0 || position_y > height)
		return true;
	return false;
}

/*------------------------------------------------------------------------------------------------------*/

void Asteroid::CopyInRenderer(SDL_Texture *texture, SDL_Renderer *renderer){
    SDL_Rect position = {(int) position_x-25*size, (int) position_y-25*size, 50*size, 50*size};

    //Ajout de la texture au rendu.
    if(SDL_RenderCopy(renderer, texture, NULL, &position)){
        SDL_Log("Erreur: chargement de l'image de l'Asteroid dans le rendu : %s\n", SDL_GetError());
    }
}

/*------------------------------------------------------------------------------------------------------*/

bool Asteroid::IsInside(float _position_x, float _position_y){
	if((_position_x >= position_x-(50*size)/2 && _position_x <= position_x+(50*size)/2) && (_position_y >= position_y-(50*size)/2 && _position_y <= position_y+(50*size)/2))
		return true;
	return false;
}

//Getters

float Asteroid::GetPositionX(){
    return position_x;
}

float Asteroid::GetPositionY(){
    return position_y;
}

int Asteroid::GetSize(){
    return size;
}
