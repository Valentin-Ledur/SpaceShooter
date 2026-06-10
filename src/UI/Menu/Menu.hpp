#ifndef __MENU__
#define __MENU__

#include <vector>
#include "defines.hpp"
#include "Game/GameStatut.hpp"
#include "UI/Button/Button.hpp"
#include "UI/TextArea/TextArea.hpp"

class Menu
{
private:
    std::vector<Button> list_button = std::vector<Button>();
    std::vector<TextArea> list_textArea = std::vector<TextArea>();
    SDL_Color background_color = WHITE;
    GameStatut statut_menu = START;

public:
    Menu();
    Menu(std::vector<Button> _list_button, std::vector<TextArea> _list_textArea, SDL_Color _background_color, GameStatut _statut_menu);
    ~Menu() {};

    void Update();
    void Display(SDL_Renderer *renderer);

    GameStatut CheckButton(int x, int y);
};

#endif