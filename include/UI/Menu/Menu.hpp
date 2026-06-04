#ifndef __MENU__
#define __MENU__

#include <vector>
#include "UI/Button/Button.hpp"
#include "UI/TextArea/TextArea.hpp"

class Menu
{
private:
    std::vector<Button> list_button;
    std::vector<TextArea> list_textArea;
    SDL_Color background_color;
    GameStatut statut_menu;

public:
    Menu();
    Menu(std::vector<Button> _list_button, std::vector<TextArea> _list_textArea, SDL_Color _background_color, GameStatut _statut_menu);
    ~Menu() {};

    void Update(SDL_Renderer *renderer, int x, int y);

    GameStatut CheckButton(int x, int y);
};

#endif