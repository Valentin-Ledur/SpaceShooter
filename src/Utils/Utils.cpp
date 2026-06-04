#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Utils/Utils.hpp"

namespace Utils
{

    // Ajoute une zone de texte au rendu.
    void AddTextToRenderer(SDL_Renderer *renderer, const char *text, int fontSize, SDL_Rect textArea, const char *fontPath, SDL_Color color)
    {
        TTF_Font *font;

        // Attribution de la police d'écriture et gestion des erreurs.
        if (fontPath != NULL)
        {
            font = TTF_OpenFont(fontPath, fontSize);
        }
        else
        {
            font = TTF_OpenFont("font/arial.ttf", fontSize);
        }

        if (font == NULL)
        {
            TTF_CloseFont(font);
            SDL_Log("Erreur: ouverture du dossier font: %s\n", SDL_GetError());
            return;
        }

        // Creation d'une surface pour la texture a ajouter au rendu.
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);

        // Gestion des erreurs.
        if (textSurface == NULL)
        {
            SDL_FreeSurface(textSurface);
            TTF_CloseFont(font);
            SDL_Log("Erreur: texte: %s\n", SDL_GetError());
            return;
        }

        // Fermeture du fichier de la police.
        TTF_CloseFont(font);

        // Creation de la texture a partir de la surface.
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Liberation de l'espace qui stocke la surface.
        SDL_FreeSurface(textSurface);

        // Gestion des erreurs.
        if (textTexture == NULL)
        {
            SDL_Log("Erreur: creation texture: %s\n", SDL_GetError());
            SDL_DestroyTexture(textTexture);
            return;
        }

        // Creation des attributs de la texture.
        if (SDL_QueryTexture(textTexture, NULL, NULL, &textArea.w, &textArea.h) != 0)
        {
            SDL_Log("Erreur: chargement texture: %s\n", SDL_GetError());
            SDL_DestroyTexture(textTexture);
            return;
        }

        // Ajout du texte au rendu.
        if (SDL_RenderCopy(renderer, textTexture, NULL, &textArea))
        {
            SDL_Log("Erreur: chargement texture: %s\n", SDL_GetError());
            SDL_DestroyTexture(textTexture);
            return;
        }

        SDL_DestroyTexture(textTexture);
    }

    SDL_Texture *CreateTexture(SDL_Renderer *renderer, std::string imagePath, SDL_Rect &rect)
    {
        SDL_Surface *imageSurface;
        // Chargement de l'image.
        imageSurface = IMG_Load(imagePath.data());

        // Gestion des erreurs.
        if (imageSurface == NULL)
        {
            SDL_Log("Erreur: chargement de l'image : %s\n", SDL_GetError());
            SDL_FreeSurface(imageSurface);
            return NULL;
        }

        // Creation de la texture a partir de la surface.
        SDL_Texture *imageTexture;
        imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

        // Liberation de l'espace qui stocke la surface.
        SDL_FreeSurface(imageSurface);

        // gestion des erreurs.
        if (imageTexture == NULL)
        {
            SDL_Log("Erreur: creation de la texture de l'image : %s\n", SDL_GetError());
            SDL_DestroyTexture(imageTexture);
            return NULL;
        }

        // Gestion des attributs de l'image.
        if (SDL_QueryTexture(imageTexture, NULL, NULL, &rect.w, &rect.h) != 0)
        {
            SDL_Log("Erreur: chargement texture: %s\n", SDL_GetError());
            SDL_DestroyTexture(imageTexture);
            return NULL;
        }

        return imageTexture;
    }
}