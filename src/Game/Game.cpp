#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utils/Utils.hpp"
#include "UI/Button/Button.hpp"
#include "UI/TextArea/TextArea.hpp"
#include "UI/Menu/Menu.hpp"
#include "Game/GameStatut.hpp"
#include "Game/Game.hpp"
#include "Projectile/Projectile.hpp"
#include "Player/Player.hpp"
#include "Enemy/Asteroid.hpp"

Game::Game()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Erreur: initialisation de SDL : %s\n", SDL_GetError());
    }

    if (TTF_Init() != 0)
    {
        SDL_Log("Erreur: initialisation de SDL_TTF : %s\n", SDL_GetError());
    }

    // Creation de la fenetre.
    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_FULLSCREEN_DESKTOP);

    // Creation du rendu.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) != 0)
    {
        SDL_Log("Erreur: initialisation de SDL_TTF : %s\n", SDL_GetError());
    }

    // Icon de la fenetre.
    SDL_Surface *icon = IMG_Load("data/joueur.png");
    SDL_SetWindowIcon(window, icon);

    SDL_GetWindowSize(window, &width, &height);

    // Initialisation des textures.
    SDL_Rect rectJoueur = {0, 0, 25, 25};
    player_texture = Utils::CreateTexture(renderer, "data/Player.png", rectJoueur);

    SDL_Rect rectProjectile = {0, 0, 5, 5};
    projectile_texture = Utils::CreateTexture(renderer, "data/projectile.png", rectProjectile);

    SDL_Rect rectAsteroid50 = {0, 0, 50, 50};
    asteroid_texture_50 = Utils::CreateTexture(renderer, "data/asteroid50.png", rectAsteroid50);

    SDL_Rect rectAsteroid100 = {0, 0, 100, 100};
    asteroid_texture_100 = Utils::CreateTexture(renderer, "data/asteroid100.png", rectAsteroid100);

    SDL_Rect rectAsteroid150 = {0, 0, 150, 150};
    asteroid_texture_150 = Utils::CreateTexture(renderer, "data/asteroid150.png", rectAsteroid150);

    score = 0;
    player = Player(width, height);
    asteroid_list = std::list<Asteroid>();

    addNewAsteroid = 0;
    addMore = 1000;
    timeNew = 500;

    // Création des Menus

    SDL_Color black = {0, 0, 0, 255};
    SDL_Color dark_gray = {50, 50, 50, 255};
    SDL_Color blue = {0, 100, 255, 255};
    SDL_Color red = {200, 0, 0, 255};

    // MENU START
    TextArea title_start = TextArea(width / 2 - 200, height / 2 - 300, 400, 100, black, "SPACE SHOOTER", 40);
    Button btn_play = Button(width / 2 - 150, height / 2 - 50, 300, 80, dark_gray, blue, "JOUER", 30, PLAY);
    Button btn_quit_start = Button(width / 2 - 150, height / 2 + 100, 300, 80, dark_gray, red, "QUITTER", 30, STOP);
    start_menu = Menu({btn_play, btn_quit_start}, {title_start}, black, START);

    // MENU PAUSE
    TextArea title_pause = TextArea(width / 2 - 150, height / 2 - 300, 300, 100, black, "PAUSE", 40);
    Button btn_resume = Button(width / 2 - 150, height / 2 - 50, 300, 80, dark_gray, blue, "REPRENDRE", 30, PLAY);
    Button btn_quit_pause = Button(width / 2 - 150, height / 2 + 100, 300, 80, dark_gray, red, "QUITTER", 30, STOP);
    pause_menu = Menu({btn_resume, btn_quit_pause}, {title_pause}, black, PAUSE);

    // MENU GAME OVER
    TextArea title_gameover = TextArea(width / 2 - 200, height / 2 - 300, 400, 100, black, "GAME OVER", 40);
    Button btn_restart = Button(width / 2 - 150, height / 2 - 50, 300, 80, dark_gray, blue, "MENU PRINCIPAL", 30, START);
    Button btn_quit_go = Button(width / 2 - 150, height / 2 + 100, 300, 80, dark_gray, red, "QUITTER", 30, STOP);
    game_over_menu = Menu({btn_restart, btn_quit_go}, {title_gameover}, black, GAME_OVER);
}

Game::~Game()
{
    SDL_DestroyTexture(asteroid_texture_50);
    SDL_DestroyTexture(asteroid_texture_100);
    SDL_DestroyTexture(asteroid_texture_150);
    SDL_DestroyTexture(projectile_texture);
    SDL_DestroyTexture(player_texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}

// Genere un nombre aleatoire compris dans [range_min, range_max[.
int Game::Random(int range_min, int range_max)
{
    int r = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    return r;
}

void Game::AddAsteroid()
{
    if (addNewAsteroid < SDL_GetTicks())
    {
        asteroid_list.push_back(Asteroid(width, height));
        addNewAsteroid += timeNew;
    }
    if (addMore < SDL_GetTicks() && timeNew > 100)
    {
        timeNew -= 50;
        addMore += 1000;
    }
}

GameStatut Game::HandleKey(SDL_Event event)
{
    switch (statut)
    {
    case START:
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                GameStatut action = start_menu.CheckButton(x, y);
                if (action == PLAY)
                    ResetGame();
                return action;
            }
        }
        return START;

    case PLAY:
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_p)
                    return PAUSE;
                if (event.key.keysym.sym == SDLK_m)
                    return STOP;

                player.HandleKey(event);
            }
            else if (event.type == SDL_KEYUP)
            {
                player.KeyRelease(event);
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                float position_x = player.GetPositionX();
                float position_y = player.GetPositionY();
                float direction_x = event.button.x - player.GetPositionX();
                float direction_y = event.button.y - player.GetPositionY();
                float norme = sqrtf(direction_x * direction_x + direction_y * direction_y);
                direction_x /= norme;
                direction_y /= norme;
                projectile_list.push_back(Projectile(position_x, position_y, direction_x, direction_y));
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                player.Angle(event);
            }
        }
        return PLAY;

    case PAUSE:
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_p))
                return PLAY;

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                return pause_menu.CheckButton(x, y);
            }
        }
        return PAUSE;

    case GAME_OVER:
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                return game_over_menu.CheckButton(x, y);
            }
        }
        return GAME_OVER;

    case STOP:
        run = false;
        return STOP;

    default:
        return STOP;
    }
}

void Game::UpdateProjectile()
{
    for (auto projectile = projectile_list.begin(); projectile != projectile_list.end();)
    {
        projectile->Move();

        bool projectile_removed = false;
        for (auto asteroid = asteroid_list.begin(); asteroid != asteroid_list.end();)
        {
            if (asteroid->IsInside(projectile->GetPositionX(), projectile->GetPositionY()))
            {
                if (asteroid->GetSize() >= 2)
                {
                    asteroid_list.emplace_back(Asteroid(asteroid->GetSize(), asteroid->GetPositionX(), asteroid->GetPositionY()));
                    asteroid_list.emplace_back(Asteroid(asteroid->GetSize(), asteroid->GetPositionX(), asteroid->GetPositionY()));
                }
                asteroid = asteroid_list.erase(asteroid);
                projectile_removed = true;
                score += __SCORE__ASTEROID__;
                break;
            }
            else
            {
                ++asteroid;
            }
        }

        if (projectile_removed || projectile->IsOutScreen(width, height))
        {
            projectile = projectile_list.erase(projectile);
        }
        else
        {
            projectile->CopyInRenderer(projectile_texture, renderer);
            ++projectile;
        }
    }
}

void Game::UpdateEnemy()
{

    // Parcours de la liste des astéroïdes
    for (auto asteroid = asteroid_list.begin(); asteroid != asteroid_list.end();)
    {
        asteroid->Move();

        if (asteroid->IsOutScreen(width, height))
        {
            asteroid = asteroid_list.erase(asteroid);
        }
        else if (asteroid->IsInside(player.GetPositionX(), player.GetPositionY()))
        {
            player.DecreaseHP(1);
            asteroid = asteroid_list.erase(asteroid);
            if (player.GetHP() <= 0)
            {
                statut = GAME_OVER;
            }
        }
        else
        {
            switch (asteroid->GetSize())
            {
            case 1:
                asteroid->CopyInRenderer(asteroid_texture_50, renderer);
                break;
            case 2:
                asteroid->CopyInRenderer(asteroid_texture_100, renderer);
                break;
            case 3:
                asteroid->CopyInRenderer(asteroid_texture_150, renderer);
                break;
            }
            ++asteroid;
        }
    }
}

void Game::UpdatePlayer()
{
    player.Move(width, height);
    player.CopyInRenderer(player_texture, renderer);
}

void Game::ResetGame()
{
    asteroid_list.clear();
    projectile_list.clear();

    player = Player(width, height);

    score = 0;

    addNewAsteroid = SDL_GetTicks();
    addMore = SDL_GetTicks() + 1000;
    timeNew = 500;
}

void Game::Update()
{
    int fps = 60;
    int desiredDelta = 1000 / fps;

    SDL_Event event = {};

    while (run)
    {
        int start = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        statut = HandleKey(event);

        switch (statut)
        {
        case START:
            break;

        case PLAY:
        {
            AddAsteroid();

            UpdateProjectile();
            UpdateEnemy();
            UpdatePlayer();
        }
        break;

        case PAUSE:
            break;

        case GAME_OVER:
            break;

        case STOP:
            run = false;
            break;

        default:
            break;
        }

        Display();

        int delta = SDL_GetTicks() - start;
        if (delta < desiredDelta)
        {
            SDL_Delay(desiredDelta - delta);
        }
    }
}

void Game::UpdateFrame()
{
    SDL_Event event = {};

    int start = SDL_GetTicks();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    statut = HandleKey(event);

    switch (statut)
    {
    case START:
        break;

    case PLAY:
    {
        AddAsteroid();

        UpdateProjectile();
        UpdateEnemy();
        UpdatePlayer();
    }
    break;

    case PAUSE:
        break;

    case GAME_OVER:
        break;

    case STOP:
        run = false;
        break;

    default:
        break;
    }

    Display();
}

void Game::Display()
{
    switch (statut)
    {
    case START:
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        start_menu.Update(renderer, x, y);
    }
    break;

    case PLAY:
    {
        SDL_Rect HUD = {(int)(width - width * 0.05), 0, 40, 20};
        SDL_Rect rectPv = {0, 0, 40, 20};
        SDL_Color white = {255, 255, 255, 255};
        Utils::AddTextToRenderer(renderer, std::to_string(score).data(), 15, HUD, NULL, white);
        Utils::AddTextToRenderer(renderer, std::to_string(player.GetHP()).data(), 15, rectPv, NULL, white);
    }
    break;

    case PAUSE:
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        pause_menu.Update(renderer, x, y);
    }
    break;

    case GAME_OVER:
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        game_over_menu.Update(renderer, x, y);
    }
    break;

    case STOP:
        run = false;
        return;
    }

    SDL_RenderPresent(renderer);
}