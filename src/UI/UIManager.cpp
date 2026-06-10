#include <string>
#include <SDL2/SDL.h>
#include "Utils/Utils.hpp"
#include "defines.hpp"
#include "UI/Menu/Menu.hpp"
#include "UI/Button/Button.hpp"
#include "UI/TextArea/TextArea.hpp"
#include "UI/UIManager.hpp"

void UIManager::Init(int _width, int _height, int *_score_ptr, int *_hp_ptr)
{
    // MENU START
    TextArea title_start = TextArea(_width / 2 - 200, _height / 2 - 300, 400, 100, BLACK, "SPACE SHOOTER", 40);
    Button btn_play = Button(_width / 2 - 150, _height / 2 - 50, 300, 80, DARK_GRAY, BLUE, "JOUER", 30, PLAY);
    Button btn_quit_start = Button(_width / 2 - 150, _height / 2 + 100, 300, 80, DARK_GRAY, RED, "QUITTER", 30, STOP);
    start = Menu({btn_play, btn_quit_start}, {title_start}, BLACK, START);

    // MENU PLAY
    TextArea _score = TextArea((int)(_width - _width * 0.05), 0, 40, 20, TRANSPARENT, _score_ptr, 15);
    TextArea _hp = TextArea(0, 0, 40, 20, TRANSPARENT, _hp_ptr, 15);
    play = Menu({}, {_score, _hp}, BLACK, PLAY);

    // MENU PAUSE
    TextArea title_pause = TextArea(_width / 2 - 150, _height / 2 - 300, 300, 100, BLACK, "PAUSE", 40);
    Button btn_resume = Button(_width / 2 - 150, _height / 2 - 50, 300, 80, DARK_GRAY, BLUE, "REPRENDRE", 30, PLAY);
    Button btn_quit_pause = Button(_width / 2 - 150, _height / 2 + 100, 300, 80, DARK_GRAY, RED, "QUITTER", 30, STOP);
    pause = Menu({btn_resume, btn_quit_pause}, {title_pause}, BLACK, PAUSE);

    // MENU GAME OVER
    TextArea title_gameover = TextArea(_width / 2 - 200, _height / 2 - 300, 400, 100, BLACK, "GAME OVER", 40);
    Button btn_restart = Button(_width / 2 - 150, _height / 2 - 50, 300, 80, DARK_GRAY, BLUE, "MENU PRINCIPAL", 30, START);
    Button btn_quit_go = Button(_width / 2 - 150, _height / 2 + 100, 300, 80, DARK_GRAY, RED, "QUITTER", 30, STOP);
    game_over = Menu({btn_restart, btn_quit_go}, {title_gameover}, BLACK, GAME_OVER);
}

GameStatut UIManager::HandleEvent(SDL_Event _event, GameStatut _current_game_statut)
{
    if (_event.key.keysym.sym == SDLK_ESCAPE && _current_game_statut == PLAY)
    {
        return PAUSE;
    }
    else if (_event.type == SDL_MOUSEBUTTONDOWN)
    {
        switch (_current_game_statut)
        {
        case START:
            return start.CheckButton(_event.button.x, _event.button.y);
            break;
        case PLAY:
            return play.CheckButton(_event.button.x, _event.button.y);
            break;
        case PAUSE:
            return pause.CheckButton(_event.button.x, _event.button.y);
            break;
        case GAME_OVER:
            return game_over.CheckButton(_event.button.x, _event.button.y);
            break;
        default:
            return _current_game_statut;
            break;
        }
    }
    else
    {
        return _current_game_statut;
    }
}

void UIManager::Update(GameStatut _current_game_statut)
{
    switch (_current_game_statut)
    {
    case START:
        start.Update();
        break;
    case PLAY:
        play.Update();
        break;
    case PAUSE:
        pause.Update();
        break;
    case GAME_OVER:
        game_over.Update();
        break;
    default:
        break;
    }
}

void UIManager::Display(SDL_Renderer *_renderer, GameStatut _current_game_statut)
{
    switch (_current_game_statut)
    {
    case START:
        start.Display(_renderer);
        break;
    case PLAY:
        play.Display(_renderer);
        break;
    case PAUSE:
        pause.Display(_renderer);
        break;
    case GAME_OVER:
        game_over.Display(_renderer);
        break;
    default:
        break;
    }
}