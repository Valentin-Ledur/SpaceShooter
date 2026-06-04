#ifndef __GAME__
#define __GAME__
#define __SPAWN__TIME__ 500
#define __TIME__LESS__ 50
#define __SCORE__ASTEROID__ 20
#define __SCORE__ALIEN__ 20

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Game/GameStatut.hpp"
#include "UI/Menu/Menu.hpp"
#include "Player/Player.hpp"
#include "Enemy/Asteroid.hpp"

class Game
{
public:
    Game();
    ~Game();

    static int Random(int range_min, int range_max);

    void AddAsteroid();
    GameStatut HandleKey(SDL_Event event);
    void Update();
    void UpdateFrame();
    void Display();

    bool run = true;
    GameStatut statut = START;

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

    void UpdateEnemy();
    void UpdateProjectile();
    void UpdatePlayer();
    void ResetGame();

    // Menu
    Menu start_menu;
    Menu pause_menu;
    Menu game_over_menu;

    // Test
    unsigned int addNewAsteroid;
    unsigned int addMore;
    unsigned int timeNew;
};
#endif