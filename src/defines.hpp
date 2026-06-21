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

// Background
const std::string START_BACKGROUND_TEXTURE_PATH = "data/game/background_start.webp";
const std::string PLAY_BACKGROUND_TEXTURE_PATH = "data/game/background_play.webp";
const std::string GAME_OVER_BACKGROUND_TEXTURE_PATH = "data/game/background_game_over.webp";


// PLAYER
const int PLAYER_SPEED = 5;
const int PLAYER_BASE_HP = 3;
const int PLAYER_WIDTH = 75;
const int PLAYER_HEIGHT = 75;
const SDL_Rect PLAYER_RECT_TEXTURE = {0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};

const int PLAYER_IDLE_FRAME = 3;
const int PLAYER_ACTIVE_FRAME = 2;
const int PLAYER_ANIMATION_SPEED = 150;

const std::string PLAYER_IDLE_1_TEXTURE_PATH = "data/player/player_idle_1.webp";
const std::string PLAYER_IDLE_2_TEXTURE_PATH = "data/player/player_idle_2.webp";
const std::string PLAYER_IDLE_3_TEXTURE_PATH = "data/player/player_idle_3.webp";

const std::string PLAYER_ACTIVE_1_TEXTURE_PATH = "data/player/player_active_1.webp";
const std::string PLAYER_ACTIVE_2_TEXTURE_PATH = "data/player/player_active_2.webp";

// PROJECTILE
const int PROJECTILE_WIDTH = 50;
const int PROJECTILE_HEIGHT = 30;
const int PROJECTILE_SPEED = 15;
const SDL_Rect PROJECTILE_RECT_TEXTURE = {0, 0, PROJECTILE_WIDTH, PROJECTILE_HEIGHT};

const int PROJECTILE_ANIMATION_SPEED = 10;
const int PROJECTILE_FRAME = 4;
const std::string PROJECTILE_1_TEXTURE_PATH = "data/projectile/projectile_1.webp";
const std::string PROJECTILE_2_TEXTURE_PATH = "data/projectile/projectile_2.webp";
const std::string PROJECTILE_3_TEXTURE_PATH = "data/projectile/projectile_3.webp";

// ASTEROID
const int ASTEROID_SCORE = 20;
const int ASTEROID_BASE_PIXEL_SIZE = 50;
const int ASTEROID_BASE_WIDTH = 50;
const int ASTEROID_BASE_HEIGHT = 50;
const SDL_Rect ASTEROID_RECT_50 = {0, 0, ASTEROID_BASE_WIDTH, ASTEROID_BASE_HEIGHT};
const SDL_Rect ASTEROID_RECT_100 = {0, 0, ASTEROID_BASE_WIDTH * 2, ASTEROID_BASE_HEIGHT * 2};
const SDL_Rect ASTEROID_RECT_150 = {0, 0, ASTEROID_BASE_WIDTH * 3, ASTEROID_BASE_HEIGHT * 3};
const int ASTEROID_TYPES = 3;

// rotation
const std::string ASTEROID_BASIC_BASE_1_TEXTURE_PATH = "data/asteroid/basic/asteroid_basic_base_1.webp";
const std::string ASTEROID_BASIC_BASE_2_TEXTURE_PATH = "data/asteroid/basic/asteroid_basic_base_2.webp";

const std::string ASTEROID_BROWN_BASE_1_TEXTURE_PATH = "data/asteroid/brown/asteroid_brown_base_1.webp";
const std::string ASTEROID_BROWN_BASE_2_TEXTURE_PATH = "data/asteroid/brown/asteroid_brown_base_2.webp";

const std::string ASTEROID_ICE_BASE_1_TEXTURE_PATH = "data/asteroid/ice/asteroid_ice_base_1.webp";
const std::string ASTEROID_ICE_BASE_2_TEXTURE_PATH = "data/asteroid/ice/asteroid_ice_base_2.webp";

// animation
const int ASTEROID_ANIMATION_SPEED = 150;
const int ASTEROID_BASIC_FRAME = 4;

const std::string ASTEROID_BASIC_1_TEXTURE_PATH = "data/asteroid/basic/asteroid_basic_1.webp";
const std::string ASTEROID_BASIC_2_TEXTURE_PATH = "data/asteroid/basic/asteroid_basic_2.webp";
const std::string ASTEROID_BASIC_3_TEXTURE_PATH = "data/asteroid/basic/asteroid_basic_3.webp";
const std::string ASTEROID_BASIC_4_TEXTURE_PATH = "data/asteroid/basic/asteroid_basic_4.webp";

const std::string ASTEROID_BROWN_1_TEXTURE_PATH = "data/asteroid/brown/asteroid_brown_1.webp";
const std::string ASTEROID_BROWN_2_TEXTURE_PATH = "data/asteroid/brown/asteroid_brown_2.webp";
const std::string ASTEROID_BROWN_3_TEXTURE_PATH = "data/asteroid/brown/asteroid_brown_3.webp";
const std::string ASTEROID_BROWN_4_TEXTURE_PATH = "data/asteroid/brown/asteroid_brown_4.webp";

const std::string ASTEROID_ICE_1_TEXTURE_PATH = "data/asteroid/ice/asteroid_ice_1.webp";
const std::string ASTEROID_ICE_2_TEXTURE_PATH = "data/asteroid/ice/asteroid_ice_2.webp";
const std::string ASTEROID_ICE_3_TEXTURE_PATH = "data/asteroid/ice/asteroid_ice_3.webp";
const std::string ASTEROID_ICE_4_TEXTURE_PATH = "data/asteroid/ice/asteroid_ice_4.webp";

#endif