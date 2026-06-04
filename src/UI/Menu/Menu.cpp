#include <SDL2/SDL.h>
#include <vector>
#include "Game/GameStatut.hpp"
#include "UI/Menu/Menu.hpp"
#include "UI/Button/Button.hpp"
#include "UI/TextArea/TextArea.hpp"

Menu::Menu()
{
    list_button = std::vector<Button>();
    list_textArea = std::vector<TextArea>();
    background_color = {0, 0, 0, 0};
    statut_menu = PLAY;
}

Menu::Menu(std::vector<Button> _list_button, std::vector<TextArea> _list_textArea, SDL_Color _background_color, GameStatut _statut_menu)
{
    list_button = _list_button;
    list_textArea = _list_textArea;
    background_color = _background_color;
    statut_menu = _statut_menu;
}

void Menu::Update(SDL_Renderer *renderer, int x, int y)
{
    for (auto &text_area : list_textArea)
        text_area.CopyInRenderer(renderer);

    for (auto &button : list_button)
    {
        button.IsInside(x, y);
        button.CopyInRenderer(renderer);
    }
}

GameStatut Menu::CheckButton(int x, int y)
{
    for (auto &button : list_button)
    {
        if (button.IsInside(x, y))
            return button.GetAction();
    }

    return statut_menu;
}