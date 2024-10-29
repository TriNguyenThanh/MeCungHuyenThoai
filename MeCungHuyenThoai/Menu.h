#pragma once

#include "function.h"

class Menu 
{
public:
	Menu();
	~Menu();
private:
	SDL_Texture* menu_texture;
	SDL_Texture* bg_texture;
	SDL_Texture* run_bg_texture;

	SDL_Rect title;
	TTF_Font* font1;

	SDL_Rect button;
	TTF_Font* font2;
};