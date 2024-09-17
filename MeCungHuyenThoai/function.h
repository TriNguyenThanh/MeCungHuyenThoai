#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "Windows.h"
#include "string"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_audio.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

static SDL_Window* g_window = NULL;   // window control
static SDL_Renderer* g_screen = NULL; // screen control
static SDL_Event g_event;             // user input control

//screen
const int SCREEN_WIDTH = 1280; 
const int SCREEN_HIGHT = 640;
const int SCREEN_BPP = 32;      //bit per pixel

#define BACKGROUND_COLOR SDL_MapRGB(load_surface->format, 180, 180, 180)

const int CORLOR_KEY_R = 180;	// Red
const int CORLOR_KEY_G = 180;	// Green
const int CORLOR_KEY_B = 180;	// Blue

const int Render_Draw_Color = 0xff;

#define TILE_SIZE 16
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define CharRunFrame 8
#define CharTeleFrame 3

#define GRAVITY 0.7
#define MAX_FALL_SPEED 6
#define PLAYER_SPEED 7
#define PLAYER_JUMP_HEIGHT 12

#define BULLET_SPEED 20

#define FPS 60

#endif // 0
