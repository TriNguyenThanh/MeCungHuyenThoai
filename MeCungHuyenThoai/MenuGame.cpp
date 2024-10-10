#include "MenuGame.h"
#include "function.h"
BaseObject g_img_menu;
int SDLMenuGame::ShowMenu(SDL_Surface* des, TTF_Font* font) 
{
	bool ret = g_img_menu.loadImg("start.png", g_screen);
	if (g_img_menu == false) {
		return 1;
	}

	const int kMenuItemNum = 2;
	SDL_Rect  pos_arr[kMenuItemNum];
	pos_arr[0].x = 200;
	pos_arr[0].y = 400;

	pos_arr[1].x = 200;
	pos_arr[1].y = 200;

	TextObject text_menu[kMenuItemNum];

	text_menu[0].SetText("Play Game");
	text_menu[0].SetColor(TextObject)
}