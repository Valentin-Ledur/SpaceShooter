#include <iostream>
#include <list>
#include <string>
#include <ctime>
#include <random>
#include <cmath>
#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "Game/Game.hpp"
#include "Projectile/Projectile.hpp"
#include "Player/Player.hpp"
#include "Enemy/Asteroid.hpp"

SDL_Texture* Game::CreateTexture(std::string imagePath, SDL_Rect rect){
    SDL_Surface *imageSurface;
    //Chargement de l'image.
    imageSurface = IMG_Load(imagePath.data());

    //Gestion des erreurs.
    if (imageSurface == NULL){
        SDL_Log("Erreur: chargement de l'image : %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        return NULL;
    }

    //Creation de la texture a partir de la surface.
    SDL_Texture *imageTexture;
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

    //Liberation de l'espace qui stocke la surface.
    SDL_FreeSurface(imageSurface);

    //gestion des erreurs.
    if (imageTexture == NULL){
        SDL_Log("Erreur: creation de la texture de l'image : %s\n", SDL_GetError());
        SDL_DestroyTexture(imageTexture);
        return NULL;
    }

    //Gestion des attributs de l'image.
    if (SDL_QueryTexture(imageTexture, NULL, NULL, &rect.w, &rect.h) != 0){
        SDL_Log("Erreur: chargement texture: %s\n", SDL_GetError());
        SDL_DestroyTexture(imageTexture);
        return NULL;
    }

    return imageTexture;
}

Game::Game(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Erreur: initialisation de SDL : %s\n", SDL_GetError());
    }
    
    
    //Creation de la fenetre.
    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_FULLSCREEN_DESKTOP);


    //Creation du rendu.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Icon de la fenetre.
    SDL_Surface *icon = IMG_Load("data/joueur.png");
    SDL_SetWindowIcon(window, icon);

    SDL_GL_GetDrawableSize(window, &width, &height);

    //Initialisation des textures.
    SDL_Rect rectJoueur = {0, 0, 25, 25};
    player_texture = CreateTexture("data/Player.png", rectJoueur);
    
    SDL_Rect rectProjectile = {0, 0, 5, 5};
    projectile_texture = CreateTexture("data/projectile.png", rectProjectile);

    SDL_Rect rectAsteroid50 = {0, 0, 50, 50};
    asteroid_texture_50 = CreateTexture("data/asteroid50.png", rectAsteroid50);

    SDL_Rect rectAsteroid100 = {0, 0, 100, 100};
    asteroid_texture_100 = CreateTexture("data/asteroid100.png", rectAsteroid100);

    SDL_Rect rectAsteroid150 = {0, 0, 150, 150};
    asteroid_texture_150 = CreateTexture("data/asteroid150.png", rectAsteroid150);

    score = 0;
    player = Player(width, height);
    asteroid_list = std::list<Asteroid>();

    addNewAsteroid = 0;
    addMore = 1000;
    timeNew = 500;
}

Game::~Game(){
    SDL_DestroyTexture(asteroid_texture_50);
    SDL_DestroyTexture(asteroid_texture_100);
    SDL_DestroyTexture(asteroid_texture_150);
    SDL_DestroyTexture(projectile_texture);
    SDL_DestroyTexture(player_texture);
}

//Genere un nombre aleatoire compris dans [range_min, range_max[.
int Game::Random(int range_min, int range_max){
    int r = ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    return r;
}

void Game::AddAsteroid(){
    if (addNewAsteroid < SDL_GetTicks()){
        asteroid_list.push_back(Asteroid(width, height));
        addNewAsteroid += timeNew;
    }
    if (addMore < SDL_GetTicks() && timeNew > 100){
            timeNew -= 50;
            addMore += 1000;
    }

}

GameStatut Game::HandleKey(SDL_Event event){
    while (SDL_PollEvent(&event) ){
        if(event.type == SDL_KEYDOWN){
            if (event.key.keysym.sym == SDLK_m){
                return STOP;
            }
            player.HandleKey(event);
        }else if (event.type == SDL_KEYUP){
            player.KeyRelease(event);
        }else if(event.type == SDL_MOUSEBUTTONDOWN ){
            float position_x = player.GetPositionX();
            float position_y = player.GetPositionY();
            float direction_x = event.button.x - player.GetPositionX();
            float direction_y = event.button.y - player.GetPositionY();
            float norme = sqrtf(direction_x * direction_x + direction_y * direction_y);
            direction_x /= norme;
            direction_y /= norme;
            projectile_list.push_back(Projectile(position_x, position_y, direction_x, direction_y));
        }else if(event.type == SDL_MOUSEMOTION){
            player.Angle(event);
        }
    }
    return PLAY;
}

void Game::Update(){
    int fps = 60;
    int desiredDelta = 1000 / fps;

    bool run = true;
    GameStatut statut = START;
    SDL_Event event = {};

    while (run) {
        int start = SDL_GetTicks();
        
        switch (statut) {
            case START:
                statut = PLAY;
                break;

            case PLAY:
                AddAsteroid();
                statut = HandleKey(event);

                // Parcours de la liste des projectiles
                for (auto projectile = projectile_list.begin(); projectile != projectile_list.end(); ) {
                    projectile->Move();

                    bool projectile_removed = false;
                    for (auto asteroid = asteroid_list.begin(); asteroid != asteroid_list.end(); ) {
                        if (asteroid->IsInside(projectile->GetPositionX(), projectile->GetPositionY())) {
                            if (asteroid->GetSize() >= 2) {
                                asteroid_list.emplace_back(Asteroid(asteroid->GetSize(), asteroid->GetPositionX(), asteroid->GetPositionY()));
                                asteroid_list.emplace_back(Asteroid(asteroid->GetSize(), asteroid->GetPositionX(), asteroid->GetPositionY()));
                            }
                            asteroid = asteroid_list.erase(asteroid); // Met à jour l'itérateur
                            projectile_removed = true;
                            score += __SCORE__ASTEROID__;
                            break; // Sortir de la boucle interne
                        } else {
                            ++asteroid;
                        }
                    }

                    if (projectile_removed || projectile->IsOutScreen(width, height)) {
                        projectile = projectile_list.erase(projectile); // Met à jour l'itérateur
                    } else {
                        projectile->CopyInRenderer(projectile_texture, renderer);
                        ++projectile;
                    }
                }

                // Parcours de la liste des astéroïdes
                for (auto asteroid = asteroid_list.begin(); asteroid != asteroid_list.end(); ) {
                    asteroid->Move();

                    if (asteroid->IsOutScreen(width, height)) {
                        asteroid = asteroid_list.erase(asteroid);
                    } else if (asteroid->IsInside(player.GetPositionX(), player.GetPositionY())) {
                        player.DecreaseHP(1);
                        asteroid = asteroid_list.erase(asteroid);
                        if (player.GetHP() <= 0) {
                            statut = STOP;
                        }
                    } else {
                        switch (asteroid->GetSize()) {
                            case 1: asteroid->CopyInRenderer(asteroid_texture_50, renderer); break;
                            case 2: asteroid->CopyInRenderer(asteroid_texture_100, renderer); break;
                            case 3: asteroid->CopyInRenderer(asteroid_texture_150, renderer); break;
                        }
                        ++asteroid;
                    }
                }

                player.Move(width, height);
                player.CopyInRenderer(player_texture, renderer);
                Display();
                break;

            case PAUSE:
                break;

            case GAME_OVER:
                break;

            case STOP:
                SDL_Quit();
                run = false;
                break;

            default:
                break;
        }

        int delta = SDL_GetTicks() - start;
        if (delta < desiredDelta) {
            SDL_Delay(desiredDelta - delta);
        }
    }
}

void Game::Display(){
    const SDL_Rect HUD = {(int) (width-width*0.05), 0, 40, 20};
    const SDL_Rect rectPv = {0, 0, 40, 20};
    const SDL_Color white = {255,255,255};
    AddTextToRenderer(renderer, std::to_string(score).data(), 15, HUD, NULL, white);
    AddTextToRenderer(renderer, std::to_string(player.GetHP()).data(), 15, rectPv, NULL, white);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}


//Ajoute une zone de texte au rendu.
void Game::AddTextToRenderer(SDL_Renderer *renderer, const char* text, int fontSize, SDL_Rect textArea, const char* fontPath, SDL_Color color){


    //Initialisation de TTF.
    if (TTF_Init() != 0){
        SDL_Log("Erreur: initialisation de SDL_TTF : %s\n", SDL_GetError());
    }
    
    TTF_Font *font;

    //Attribution de la police d'écriture et gestion des erreurs.
    if (fontPath != NULL){
        font = TTF_OpenFont(fontPath, fontSize);
    }else{
        font = TTF_OpenFont("font/arial.ttf", fontSize);
    }

    if (font == NULL){
        TTF_CloseFont(font);
        SDL_Log("Erreur: ouverture du dossier font: %s\n", SDL_GetError());
    }

    //Creation d'une surface pour la texture a ajouter au rendu.
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);

    //Gestion des erreurs.
    if (textSurface == NULL){
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        SDL_Log("Erreur: texte: %s\n", SDL_GetError());
    }

    //Fermeture du fichier de la police.
    TTF_CloseFont(font);

    //Creation de la texture a partir de la surface.
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    //Liberation de l'espace qui stocke la surface.
    SDL_FreeSurface(textSurface);

    //Gestion des erreurs.
    if (textTexture == NULL){
        SDL_Log("Erreur: creation texture: %s\n", SDL_GetError());
        SDL_DestroyTexture(textTexture);
    }

    //Creation des attributs de la texture.
    if (SDL_QueryTexture(textTexture, NULL, NULL, &textArea.w, &textArea.h) != 0){
        SDL_Log("Erreur: chargement texture: %s\n", SDL_GetError());
        SDL_DestroyTexture(textTexture);
    }

    //Ajout du texte au rendu.
    if (SDL_RenderCopy(renderer, textTexture, NULL, &textArea)){
        SDL_Log("Erreur: chargement texture: %s\n", SDL_GetError());
        SDL_DestroyTexture(textTexture);
    }

    SDL_DestroyTexture(textTexture);
    TTF_Quit();
}