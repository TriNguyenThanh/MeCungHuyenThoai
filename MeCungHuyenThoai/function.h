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

static SDL_Window* window = NULL;   // window control
static SDL_Renderer* screen = NULL; // screen control
static SDL_Event event;             // user input control

//screen
const int SIDE_MENU_WIDTH = 150;

const int SCREEN_WIDTH = 1152 + SIDE_MENU_WIDTH;
const int SCREEN_HIGHT = 720;
const int SCREEN_BPP = 32;      //bit per pixel

#define BACKGROUND_COLOR SDL_MapRGB(load_surface->format, 180, 180, 180)

const int CORLOR_KEY_R = 180;	// Red
const int CORLOR_KEY_G = 180;	// Green
const int CORLOR_KEY_B = 180;	// Blue

const int Render_Draw_Color_red = 18; // mau nen
const int Render_Draw_Color_green = 15;
const int Render_Draw_Color_blue = 34;
const int Render_Draw_Color = 0;

#define TILE_SIZE 48
#define TILE_COUNT 20
#define MAX_MAP_X 24
#define MAX_MAP_Y 15

#define FPS 60

struct InputType
{
	int left;
	int right;
	int jump;
	int shoot;
	int interact;
};

#endif // 0