#include <SDL2/SDL.h>
#include <vector>
#include "Utils/Utils.hpp"
#include "Game/GameStatut.hpp"
#include "UI/Menu/Menu.hpp"
#include "UI/Button/Button.hpp"
#include "UI/TextArea/TextArea.hpp"

Menu::Menu(SDL_Renderer *_renderer, std::vector<Button> _list_button, std::vector<TextArea> _list_textArea, std::string _texture_path, SDL_Rect _screen_rect, GameStatut _statut_menu)
{
    list_button = _list_button;
    list_textArea = _list_textArea;
    screen_rect = _screen_rect;
    background_texture = Utils::CreateTexture(_renderer, _texture_path, _screen_rect);
    statut_menu = _statut_menu;
}

void Menu::Update()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    for (auto &button : list_button)
    {
        button.IsInside(x, y);
    }
}

void Menu::Display(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, background_texture, NULL, &screen_rect);

    for (auto &text_area : list_textArea)
        text_area.CopyInRenderer(renderer);

    for (auto &button : list_button)
        button.CopyInRenderer(renderer);
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