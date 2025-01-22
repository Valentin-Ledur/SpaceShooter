#ifndef __GAME__
#define __GAME__
#define __SPAWN__TIME__ 500
#define __TIME__LESS__ 50
#define __SCORE__ASTEROID__ 20
#define __SCORE__ALIEN__ 20

#include <list>
#include <string>
#include <../include/SDL2/SDL.h>
#include <../include/SDL2/SDL_image.h>
#include "../include/Player/Player.hpp"
#include "../include/Enemy/Asteroid.hpp"

typedef enum GameStatut{
    START,
    PLAY,
    PAUSE,
    GAME_OVER,
    STOP
}GameStatut;

class Game
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int score;
    int width;
    int height;
    Player player;
    std::list<Asteroid> asteroid_list;
    std::list<Projectile> projectile_list;
    SDL_Texture *player_texture;
    SDL_Texture *projectile_texture;
    SDL_Texture *asteroid_texture_50;
    SDL_Texture *asteroid_texture_100;
    SDL_Texture *asteroid_texture_150;
    SDL_Texture* CreateTexture(std::string imagePath, SDL_Rect rect);
    void AddTextToRenderer(SDL_Renderer *renderer, char* text, int fontSize, SDL_Rect textArea, char* fontPath, SDL_Color color);

    //Test

    unsigned int addNewAsteroid;
    unsigned int addMore;
    unsigned int timeForMore;

public:
    Game();
    ~Game();
    static int Random(int range_min, int range_max);
    
    void AddAsteroid();
    GameStatut HandleKey(SDL_Event event);
    void Update();
    void Display();

};
#endif 