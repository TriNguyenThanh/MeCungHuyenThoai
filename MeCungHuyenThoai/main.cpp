#include "function.h"
#include "BaseObject.h"

BaseObject background_;

bool init() {
	bool success = true;
	// chuan bi moi truong tao cua so, render, am thanh
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		success = false;
	else
	{
		// 1 la khu rang cua
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		//tao cua so
		g_window = SDL_CreateWindow("ME CUNG HUYEN THOAI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HIGHT, SDL_WINDOW_SHOWN);

		if (g_window == nullptr)
			success = false;
		else
		{
			// tao khoi tao screen control de ve object
			g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if (g_screen == NULL)
				success = false;
			else
			{

				SDL_SetRenderDrawColor(g_screen, Render_Draw_Color, Render_Draw_Color, Render_Draw_Color, Render_Draw_Color);
				int imgFlag = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlag) && imgFlag))
					success = false;
			}
		}
	}

	return success;
}	

bool loadBackground() {
	return background_.loadImg();
}

void close() {
	background_.free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	
	return 0;
}