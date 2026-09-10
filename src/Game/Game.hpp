#ifndef __GAME__
#define __GAME__

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include "defines.hpp"
#include "Game/GameStatut.hpp"
#include "UI/UIManager.hpp"
#include "Projectile/ProjectileManager.hpp"
#include "Player/PlayerManager.hpp"
#include "Enemy/EnemyManager.hpp"

#if PYTHON || true
#include "Game/AIData.hpp"
#endif

class Game
{
private:
    int score = 0;
    int last_score = 0;
    int width = 0;
    int height = 0;
    bool run = true;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    GameStatut statut = START;

    SDL_Rect rect_background = {0, 0, 0, 0};
    SDL_Texture *play_background = NULL;

    UIManager ui_manager;
    ProjectileManager projectile_manager;
    PlayerManager player_manager;
    EnemyManager enemy_manager;

#if PYTHON || true
    bool show_ia_play = false;
    void HandleAIOutput(AIDataOutput _ai_data_output);
    std::vector<float> GetAIInput(AIDataOutput _ai_data_output);
#endif

    void HandleEvent(SDL_Event _event);
    void Update();
    void Display();
    void CheckCollision();

public:
    Game();
    ~Game();

    void Run();
    bool IsRunning() { return run; }

#if PYTHON || true
    void Reset();
    AIDataInput Step(AIDataOutput _ia_data_outpu);
#endif
};

#endif