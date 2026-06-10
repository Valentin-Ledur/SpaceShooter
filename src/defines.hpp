#ifndef __SPACE_SHOOTER_DEFINES__
#define __SPACE_SHOOTER_DEFINES__
#include <string>
#include <SDL2/SDL.h>

// SDL_RECT
const SDL_Rect BASE_RECT = {0, 0, 0, 0};

// SDL_Point
const SDL_Point BASE_POINT = {0, 0};

// COLOR
const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};
const SDL_Color DARK_GRAY = {50, 50, 50, 255};
const SDL_Color TRANSPARENT = {0, 0, 0, 0};

// TEXTURE RECTANGLE
const SDL_Rect PLAYER_RECT_TEXTURE = {0, 0, 25, 25};
const SDL_Rect PROJECTILE_RECT_TEXTURE = {0, 0, 5, 5};
const SDL_Rect ASTEROID_RECT_50 = {0, 0, 50, 50};
const SDL_Rect ASTEROID_RECT_100 = {0, 0, 100, 100};
const SDL_Rect ASTEROID_RECT_150 = {0, 0, 150, 150};

// TEXTURE PATH
const std::string PLAYER_TEXTURE_PATH = "data/player.png";
const std::string PROJECTILE_TEXTURE_PATH = "data/projectile.png";
const std::string ASTEROID_TEXTURE_50_PATH = "data/asteroid_50.png";
const std::string ASTEROID_TEXTURE_100_PATH = "data/asteroid_100.png";
const std::string ASTEROID_TEXTURE_150_PATH = "data/asteroid_150.png";

// PLAYER
const int PLAYER_SPEED = 5;
const int PLAYER_BASE_HP = 3;

// PROJECTILE
const int PROJECTILE_SIZE = 5;
const int PROJECTILE_SPEED = 15;

// ASTEROID
const int ASTEROID_SCORE = 20;

#endif