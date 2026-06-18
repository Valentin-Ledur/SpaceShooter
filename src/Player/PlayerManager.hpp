#ifndef __PLAYER_MANAGER__
#define __PLAYER_MANAGER__

#include <string>
#include <SDL2/SDL.h>
#include "defines.hpp"
#include "Game/GameStatut.hpp"
#include "Animation/Animation.hpp"
#include "Player/Player.hpp"

class PlayerManager
{
private:
    Player player = Player();
    SDL_Point start_position = BASE_POINT;
    SDL_Rect texture_rectangle = BASE_RECT;
    
    Animation idle;
    Animation active;

    double rotation = 0.0;
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

    bool IsMoving();
    void MovePlayer(int _width, int _height);

public:
    PlayerManager() {};
    ~PlayerManager() {};

    void Init(int _hp, SDL_Point _position, SDL_Renderer *_renderer);
    void HandleEvent(SDL_Event _event, GameStatut _statut);
    void Update(int _width, int _height);
    void Display(SDL_Renderer *_renderer);
    void Reset();
    void Clean();
    int *GetPlayerHpPtr() { return player.GetHp(); }
    SDL_Point *GetPlayerPositionPtr() { return player.GetPosition(); }
};

#endif