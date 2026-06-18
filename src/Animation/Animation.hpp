#ifndef __ANIMATION__
#define __ANIMATION__

#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Animation
{
private:
    std::vector<SDL_Texture *> texture_vector = std::vector<SDL_Texture *>();
    int timer = 0;
    int width = 0;
    int height = 0;

public:
    Animation() {}
    Animation(std::vector<std::string> _textures_path, int _timer, SDL_Rect _textures_rect, SDL_Renderer *_renderer);
    ~Animation() {}

    void Display(SDL_Renderer *_renderer, SDL_Point _position);
    void DisplayWithRotation(SDL_Renderer *_renderer, SDL_Point _position, double _angle);
    void Clean();
};

#endif