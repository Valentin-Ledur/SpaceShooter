#ifndef __UICOMPONENT__
#define __UICOMPONENT__

#include <string>
#include <SDL2/SDL.h>
#include "Game/GameStatut.hpp"

class UIComponent
{
private:
    std::string text = "";
    SDL_Texture* background_texture = nullptr;

public:
    UIComponent(SDL_Renderer* _renderer, std::string _text, std::string _texture_path);
    ~UIComponent() { SDL_DestroyTexture background_texture; }
    void Display(SDL_Renderer* _renderer, SDL_Point _mouse_position);
    inline virtual bool IsInteractable() { return false; }
};


#endif