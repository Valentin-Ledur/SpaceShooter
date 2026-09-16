#include <iostream>
#include <list>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "defines.hpp"
#include "Game/GameStatut.hpp"
#include "UI/UIManager.hpp"
#include "Projectile/ProjectileManager.hpp"
#include "Player/PlayerManager.hpp"
#include "Enemy/EnemyManager.hpp"
#include "Game/Game.hpp"
#include "Enemy/Asteroid/Asteroid.hpp"

#if PYTHON
#include "Game/AIData.hpp"
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

Game::Game()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur: initialisation de SDL : %s\n", SDL_GetError());
    }

    int imgFlags = IMG_INIT_WEBP;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        SDL_Log("Erreur: initialisation de SDL_image : %s\n", IMG_GetError());
    }

    if (TTF_Init() != 0)
    {
        SDL_Log("Erreur: initialisation de SDL_TTF : %s\n", SDL_GetError());
    }

    // Creation de la fenetre.

#if PYTHON
    SDL_WindowFlags window_flags = SDL_WINDOW_HIDDEN; // Fenêtre masquée par défaut pour l'entraînement rapide
#else
    SDL_WindowFlags window_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif

    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, window_flags);

    // Creation du rendu.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) != 0)
    {
        SDL_Log("Erreur: initialisation de SDL_TTF : %s\n", SDL_GetError());
    }

    // Icon de la fenetre.
    SDL_Surface *icon = IMG_Load(PLAYER_ACTIVE_1_TEXTURE_PATH.data());
    SDL_SetWindowIcon(window, icon);

    SDL_GetWindowSize(window, &width, &height);

    if (width < height)
    {
        int tmp = width;
        width = height;
        height = tmp;
    }

    rect_background = {0, 0, width, height};

    play_background = Utils::CreateTexture(renderer, PLAY_BACKGROUND_TEXTURE_PATH, rect_background);

    SDL_Point spawn = {int(width / 2.f), int(height / 2.f)};

    player_manager.Init(PLAYER_BASE_HP, spawn, renderer);
    ui_manager.Init(renderer, width, height, &score, &last_score, player_manager.GetPlayerHpPtr());
    enemy_manager.Init(renderer);
    projectile_manager.Init(renderer);
}

Game::~Game()
{
    player_manager.Clean();
    enemy_manager.Clean();
    projectile_manager.Clean();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}

void Game::HandleEvent(SDL_Event _event)
{
    while (SDL_PollEvent(&_event))
    {
#if !PYTHON
        switch (statut)
        {
        case START:
        {
            statut = ui_manager.HandleEvent(_event, statut);
        }
        break;

        case PLAY:
        {
            statut = ui_manager.HandleEvent(_event, statut);
            player_manager.HandleEvent(_event, statut);
            projectile_manager.HandleEvent(_event, *(player_manager.GetPlayerPositionPtr()), statut);
        }
        break;

        case PAUSE:
        {
            statut = ui_manager.HandleEvent(_event, statut);
        }
        break;

        case GAME_OVER:
        {
            statut = ui_manager.HandleEvent(_event, statut);
        }
        break;

        case STOP:
        {
        }
        break;
        default:
            break;
        }
#else
        if (_event.key.keysym.sym == SDLK_e)
        {
            show_ia_play = !show_ia_play;
        }
#endif
    }
}

#if !PYTHON
void Game::Update()
{
    ui_manager.Update(statut);
    player_manager.Update(width, height);
    enemy_manager.Update(width, height);
    projectile_manager.Update(width, height);
}
#endif

void Game::Display()
{
    ui_manager.Display(renderer, statut);
    player_manager.Display(renderer);
    enemy_manager.Display(renderer);
    projectile_manager.Display(renderer);
}

void Game::CheckCollision()
{
    auto *list_projectiles = projectile_manager.GetPlayerProjectilePtr();
    auto *list_asteroids = enemy_manager.GetAsteroidListPtr();

    for (auto p = list_projectiles->begin(); p != list_projectiles->end();)
    {
        bool projectile_detruit = false;

        for (auto a = list_asteroids->begin(); a != list_asteroids->end();)
        {
            SDL_Rect asteroid_rect = {a->GetPosition()->x - 25 * a->GetSize(), a->GetPosition()->y - 25 * a->GetSize(), 50 * a->GetSize(), 50 * a->GetSize()};

            if (SDL_PointInRect(p->GetPosition(), &asteroid_rect))
            {

                if (enemy_manager.AddAsteroid(&(*a)) == true)
                {
                    score += ASTEROID_SCORE;
#if PYTHON
                    current_ia_score += 1;
#endif
                    a = list_asteroids->erase(a);
                }

                projectile_detruit = true;
                break;
            }
            else
            {
                ++a;
            }
        }

        if (projectile_detruit)
        {
            p = list_projectiles->erase(p);
        }
        else
        {
            ++p;
        }
    }

    for (auto a = list_asteroids->begin(); a != list_asteroids->end();)
    {
        SDL_Rect asteroid_rect = {a->GetPosition()->x - 25 * a->GetSize(), a->GetPosition()->y - 25 * a->GetSize(), 50 * a->GetSize(), 50 * a->GetSize()};

        if (SDL_PointInRect(player_manager.GetPlayerPositionPtr(), &asteroid_rect))
        {
            int *hp = player_manager.GetPlayerHpPtr();
            *hp = *hp - 1;
#if PYTHON
            current_ia_score -= 10;
#endif
            if (*hp <= 0)
            {
                statut = GAME_OVER;
            }

            player_manager.HandleEffect(a->GetEffect());
            a = list_asteroids->erase(a);
        }
        else
        {
            ++a;
        }
    }
}

#if !PYTHON
void Game::Run()
{
    int fps = 60;
    int desiredDelta = 1000 / fps;

    SDL_Event event = {};

#ifndef __EMSCRIPTEN__
    while (run)
    {
#endif
        unsigned int start = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        HandleEvent(event);

        switch (statut)
        {
        case START:
        {
            projectile_manager.Reset();
            enemy_manager.Reset();
            player_manager.Reset();
            score = 0;

            ui_manager.Update(statut);
            ui_manager.Display(renderer, statut);
        }
        break;

        case PLAY:
        {
            ui_manager.Update(statut);
            player_manager.Update(width, height);
            enemy_manager.Update(width, height);
            projectile_manager.Update(width, height);

            CheckCollision();

            ui_manager.Display(renderer, statut);
            enemy_manager.Display(renderer);
            player_manager.Display(renderer);
            projectile_manager.Display(renderer);
        }
        break;

        case PAUSE:
        {
            ui_manager.Update(statut);

            enemy_manager.Display(renderer);
            player_manager.Display(renderer);
            ui_manager.Display(renderer, statut);
        }
        break;

        case GAME_OVER:
        {
            last_score = score;
            ui_manager.Update(statut);
            ui_manager.Display(renderer, statut);
        }
        break;

        case STOP:
        {
            run = false;
        }
        break;
        default:
            break;
        }

        SDL_RenderPresent(renderer);

        int delta = SDL_GetTicks() - start;
        if (delta < desiredDelta)
        {
            SDL_Delay(desiredDelta - delta);
        }
#ifndef __EMSCRIPTEN__
    }
#endif
}

#endif

#if PYTHON

#include <algorithm>

void Game::HandleAIOutput(AIDataOutput _ai_data_output)
{

    player_manager.HandleAIData(_ai_data_output);
    projectile_manager.HandleAIOutput(_ai_data_output, *(player_manager.GetPlayerPositionPtr()));
}

std::vector<float> Game::GetAIInput()
{
    std::vector<float> inputs;

    SDL_Point *p_pos = player_manager.GetPlayerPositionPtr();

    inputs.push_back(float(p_pos->x) / width);
    inputs.push_back(float(p_pos->y) / height);
    inputs.push_back(float(*(player_manager.GetPlayerHpPtr())));

    auto *asteroids = enemy_manager.GetAsteroidListPtr();
    std::vector<Asteroid *> sorted_asteroids;
    sorted_asteroids.reserve(asteroids->size());

    for (auto &a : *asteroids)
    {
        sorted_asteroids.push_back(&a);
    }

    std::sort(sorted_asteroids.begin(), sorted_asteroids.end(), [p_pos](Asteroid *a, Asteroid *b)
              {
        float distA = std::hypot(a->GetPosition()->x - p_pos->x, a->GetPosition()->y - p_pos->y);
        float distB = std::hypot(b->GetPosition()->x - p_pos->x, b->GetPosition()->y - p_pos->y);
        return distA < distB; });

    const int MAX_ASTEROIDS = 10;
    int count = 0;
    for (auto *a : sorted_asteroids)
    {
        if (count >= MAX_ASTEROIDS)
            break;

        inputs.push_back(static_cast<float>(a->GetPosition()->x - p_pos->x) / width);
        inputs.push_back(static_cast<float>(a->GetPosition()->y - p_pos->y) / height);
        inputs.push_back(static_cast<float>(a->GetDirection()->x) / 10.0f);
        inputs.push_back(static_cast<float>(a->GetDirection()->y) / 10.0f);
        inputs.push_back(static_cast<float>(a->GetSize()) / 3.0f);
        count++;
    }

    while (count < MAX_ASTEROIDS)
    {
        inputs.push_back(0.0f);
        inputs.push_back(0.0f);
        inputs.push_back(0.0f);
        inputs.push_back(0.0f);
        inputs.push_back(0.0f);
        count++;
    }

    inputs.push_back(float(current_ia_score));
    inputs.push_back(float(score));

    return inputs;
}

std::vector<float> Game::Reset()
{
    player_manager.Reset();
    enemy_manager.Reset();
    projectile_manager.Reset();

    score = 0;

    statut = PLAY;

    return GetAIInput();
}

std::vector<float> Game::Step(AIDataOutput _ai_data_output)
{
    SDL_Event event = {};

    current_ia_score = 0.f;

    HandleAIOutput(_ai_data_output);

    player_manager.Update(width, height, _ai_data_output);
    enemy_manager.Update(width, height);
    projectile_manager.Update(width, height);

    CheckCollision();

    if (show_ia_play)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        ui_manager.Display(renderer, PLAY);
        enemy_manager.Display(renderer);
        player_manager.Display(renderer);
        projectile_manager.Display(renderer);

        SDL_RenderPresent(renderer);
    }

    return GetAIInput();
}

#endif