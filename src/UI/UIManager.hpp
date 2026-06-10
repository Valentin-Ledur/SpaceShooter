#ifndef __UI_MANAGER__
#define __UI_MANAGER__
#include <string>
#include <SDL2/SDL.h>
#include "Utils/Utils.hpp"
#include "defines.hpp"
#include "Game/GameStatut.hpp"
#include "UI/Menu/Menu.hpp"
#include "UI/Button/Button.hpp"
#include "UI/TextArea/TextArea.hpp"

class UIManager
{
private:
    Menu start = Menu();
    Menu play = Menu();
    Menu pause = Menu();
    Menu game_over = Menu();

public:
    UIManager() {};
    ~UIManager() {};

    void Init(int _width, int _height, int *_score_ptr, int *_hp_ptr);
    GameStatut HandleEvent(SDL_Event _event, GameStatut _current_game_statut);
    void Update(GameStatut _current_game_statut);
    void Display(SDL_Renderer *_renderer, GameStatut _current_game_statut);
};

#endif