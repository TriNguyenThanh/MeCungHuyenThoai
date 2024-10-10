#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "Windows.h"
#include "string"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_audio.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <vector>

#define TILE_SIZE 64
#define TILE_COUNT 20
#define MAX_MAP_X 30
#define MAX_MAP_Y 16

static SDL_Window* window = NULL;   // window control
static SDL_Renderer* screen = NULL; // screen control
static SDL_Event event;             // user input control

//screen
const int SCREEN_WIDTH = TILE_SIZE * MAX_MAP_X;
const int SCREEN_HIGHT = TILE_SIZE * MAX_MAP_Y;
const int SCREEN_BPP = 32;      //bit per pixel

#define BACKGROUND_COLOR SDL_MapRGB(surface->format, 180, 180, 180)

const int CORLOR_KEY_R = 180;	// Red
const int CORLOR_KEY_G = 180;	// Green
const int CORLOR_KEY_B = 180;	// Blue

const int Render_Draw_Color_red = 18; // mau nen
const int Render_Draw_Color_green = 15;
const int Render_Draw_Color_blue = 34;

#define FPS 60
#define PAUSE_TIME 1500

#define GRAVITY 0.6
#define PLAYER_MAX_FALL_SPEED 15
#define PLAYER_SPEED 3
#define PLAYER_JUMP 10
#define PLAYER_CLIMB 2
#define CHAR_FRAME 20
#define FRAME_SPACE 86

#define BULLET_SPEED 16

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
	RIGHT = 1
};
#endif // 0