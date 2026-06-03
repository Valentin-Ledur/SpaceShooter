#include "Game/Game.hpp"
#include <iostream>

Game* game = nullptr;

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
void emscripten_main_loop()
{
    if (game->run)
        game->UpdateFrame();
    else 
        emscripten_cancel_main_loop();
}
#endif

//Windows : g++ src/main.cpp src/Player/*.cpp src/Projectile/*.cpp src/Enemy/*.cpp src/Game/*.cpp -o bin/main -Wall -I include -L lib -lm -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2
//Web emcmake cmake .. -DCMAKE_BUILD_TYPE=Release cmake build .
int main(int argc, char *argv[]) {
    game = new Game();

#ifdef __EMSCRIPTEN__
    // 0 = utiliser les FPS du navigateur (généralement 60), 1 = simuler une boucle infinie
    emscripten_set_main_loop(emscripten_main_loop, 0, 1);
#else
    game->Update();
#endif

    delete game;
    return 0;
}