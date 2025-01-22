#include "../include/Game/Game.hpp"
#include <iostream>
#include <list>

//Windows : g++ src/main.cpp src/Player/*.cpp src/Projectile/*.cpp src/Enemy/*.cpp src/Game/*.cpp -o bin/main -Wall -I include -L lib -lm -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2


int main(int argc, char *argv[]){
    Game game = Game();
    game.Update();
    return 0;
}




