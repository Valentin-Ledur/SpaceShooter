#ifndef __MENU__
#define __MENU__

#include <vector>
#include <string>
#include "defines.hpp"
#include "Game/GameStatut.hpp"
#include "UI/Button/Button.hpp"
#include "UI/TextArea/TextArea.hpp"

class Menu
{
private:
    std::vector<Button> list_button = std::vector<Button>();
    std::vector<TextArea> list_textArea = std::vector<TextArea>();
    SDL_Rect screen_rect = {0, 0, 0, 0};
    SDL_Texture *background_texture = nullptr;
    GameStatut statut_menu = START;

public:
    Menu() {}
    Menu(SDL_Renderer *_renderer, std::vector<Button> _list_button, std::vector<TextArea> _list_textArea, std::string _texture_path, SDL_Rect _screen_rect, GameStatut _statut_menu);
    ~Menu() {};

    void Update();
    void Display(SDL_Renderer *renderer);
    GameStatut CheckButton(int x, int y);
    void Clean() { SDL_DestroyTexture(background_texture); }
};

#endif