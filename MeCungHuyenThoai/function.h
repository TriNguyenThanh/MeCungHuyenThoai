#pragma once

#include "Windows.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <math.h>

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_audio.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "FpsControl.h"
#include "json.hpp"

using JSON = nlohmann::json;

const bool ADMIN = true;

// thong so tile map
#define TILE_SIZE 64
#define TILE_COUNT 20
#define MAX_MAP_X 30
#define MAX_MAP_Y 16

// cong cu quan ly cua so game va quan ly game
static SDL_Window* window = NULL;   // window control
static SDL_Renderer* screen = NULL; // screen control
static SDL_Event event;             // user input control

//screen
const int SCREEN_WIDTH = 1920;
const int SCREEN_HIGHT = 1080;
const int SCREEN_BPP = 32;      //bit per pixel

#define BACKGROUND_COLOR SDL_MapRGB(surface->format, 180, 180, 180)

const int CORLOR_KEY_R = 180;	// Red
const int CORLOR_KEY_G = 180;	// Green
const int CORLOR_KEY_B = 180;	// Blue

const int Render_Draw_Color_red = 18; // mau nen
const int Render_Draw_Color_green = 15;
const int Render_Draw_Color_blue = 34;

// text color
const std::string UTM_Khuccamta = "assets\\screen\\font\\UTM_Khuccamta.ttf";
const std::string Deutschland = "assets\\screen\\font\\Deutschland.ttf";
const SDL_Color RED = { 255, 0, 0 };
const SDL_Color GREEN = { 0, 255, 0 };
const SDL_Color BLUE = { 0, 0, 255 };
const SDL_Color BLACK = { 0, 0, 0 };
const SDL_Color WHITE = { 255, 255, 255 };
const SDL_Color YELLOW = { 246, 255, 0 };

// FPS control
const int FPS = 60;

// thong so cua moi truong
#define GRAVITY 0.8

// thong so cua nguoi choi
#define PLAYER_MAX_FALL_SPEED 15
#define PLAYER_JUMP 12
#define DASH_SPEED  2
#define PLAYER_SPEED  3
#define PLAYER_CLIMB  2
#define CHAR_FRAME 20
#define FRAME_SPACE 86
#define RESPAWN_TIME 60
#define UNDEAD_TIME 90
#define BULLET_SPEED 13
#define BULLET_MANA_TAKE 10
#define MANA_BOTTLE_VALUE1 15
#define MANA_BOTTLE_VALUE2 20

#define BAT_SPEED 2
#define MAGMA_BALL_SPEED 12.0
#define DRAGON_FIRE_SPEED 20.0

#define SLOW_FRAME_RENDER 4

struct InputType
{
	int left;
	int right;
	int jump;
	int shoot;
	int interact;
	int climb;
};

enum walk_type {
	LEFT = -1,
	RIGHT = 1,
	UP = -2,
	DOWN = 2,
	STAND = 0,
	HIDDEN = 0,
	SHOW = 255
};

int ABS(int a);
int random(int start, int end);