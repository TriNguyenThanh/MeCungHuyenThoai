#pragma once

#include "function.h"

class Menu 
{
public:
	Menu();
	~Menu();
	void setText(std::string title_, std::string button1, std::string button2);
	void setFontSize(int title_, int button_);
	void setRect(
		int title_x, int title_y,
		int button1_x, int button1_y,
		int button2_x, int button2_y);
	bool loadImg(std::string file1, std::string file2, std::string file3, std::string file4, SDL_Renderer* scr);
	void update();
	void hover(SDL_Renderer* scr);
	void click(SDL_Renderer* scr, SDL_Event evn, bool& button1, bool &button2);
	void render(SDL_Renderer* scr);
private:
	SDL_Texture* menu_texture;
	SDL_Texture* bg_texture;
	SDL_Texture* run_bg_texture;
	SDL_Rect run_bg_rect;

	std::string title_text;
	SDL_Texture* title_texture;
	int title_size;
	SDL_Rect title;
	TTF_Font* font1;

	std::string button1_text;
	SDL_Texture* button1_texture;
	SDL_Rect button1;
	bool button1_is_hover;

	std::string button2_text;
	SDL_Texture* button2_texture;
	SDL_Rect button2;
	bool button2_is_hover;
	
	TTF_Font* font2;
	int button_size;
};

class GameMenu {
private:
	bool quit;
	bool start;
	bool pause;
	bool lose;
	bool win;
public:
};