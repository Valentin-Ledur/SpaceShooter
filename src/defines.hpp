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

const std::string PROJECTILE_TEXTURE_PATH = "data/projectile.png";
const std::string ASTEROID_TEXTURE_50_PATH = "data/asteroid_50.png";
const std::string ASTEROID_TEXTURE_100_PATH = "data/asteroid_100.png";
const std::string ASTEROID_TEXTURE_150_PATH = "data/asteroid_150.png";

// PLAYER
const int PLAYER_SPEED = 5;
const int PLAYER_BASE_HP = 3;
const int PLAYER_WIDTH = 75;
const int PLAYER_HEIGHT = 75;

const int PLAYER_IDLE_FRAME = 3;
const int PLAYER_ACTIVE_FRAME = 2;
const int PLAYER_ANIMATION_SPEED = 150;

const std::string PLAYER_IDLE_1_TEXTURE_PATH = "data/player/player_idle_1.png";
const std::string PLAYER_IDLE_2_TEXTURE_PATH = "data/player/player_idle_2.png";
const std::string PLAYER_IDLE_3_TEXTURE_PATH = "data/player/player_idle_3.png";

const std::string PLAYER_ACTIVE_1_TEXTURE_PATH = "data/player/player_active_1.png";
const std::string PLAYER_ACTIVE_2_TEXTURE_PATH = "data/player/player_active_2.png";

// PROJECTILE
const int PROJECTILE_SIZE = 5;
const int PROJECTILE_SPEED = 15;

// ASTEROID
const int ASTEROID_SCORE = 20;
const int ASTEROID_BASE_PIXEL_SIZE = 50;

// rotation
const std::string ASTEROID_BASIC_BASE_1_TEXTURE_PATH = "data/asteroid/asteroid_basic_base_1.png";
const std::string ASTEROID_BASIC_BASE_2_TEXTURE_PATH = "data/asteroid/asteroid_basic_base_2.png";

// animation
const std::string ASTEROID_BASIC_1_TEXTURE_PATH = "data/asteroid/asteroid_basic_1.png";
const std::string ASTEROID_BASIC_2_TEXTURE_PATH = "data/asteroid/asteroid_basic_2.png";
const std::string ASTEROID_BASIC_3_TEXTURE_PATH = "data/asteroid/asteroid_basic_3.png";
const std::string ASTEROID_BASIC_4_TEXTURE_PATH = "data/asteroid/asteroid_basic_4.png";

#endif