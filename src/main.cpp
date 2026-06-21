#include "Game/Game.hpp"

Game *game = nullptr;

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
void emscripten_main_loop()
{
    if (game->IsRunning())
        game->Run();
    else
    {
        emscripten_cancel_main_loop();
        EM_ASM(window.close(););
    }
}

#endif

int main(int argc, char *argv[])
{
    game = new Game();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(emscripten_main_loop, 0, 1);
#else
    game->Run();
#endif

    delete game;
    return 0;
}

// 1818 lignes de C++