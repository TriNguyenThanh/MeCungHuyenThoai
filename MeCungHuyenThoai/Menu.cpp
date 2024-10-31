#include "Menu.h"

Menu::Menu()
{
	menu_texture = nullptr;
	bg_texture = nullptr;
	run_bg_texture = nullptr;
	title_texture = nullptr;
	button1_texture = nullptr;
	button2_texture = nullptr;

	font1 = font2 = nullptr;

	title_text = button1_text = button2_text = "none";
	title_size = button_size = 0;

	run_bg_rect.x = run_bg_rect.y = run_bg_rect.w = run_bg_rect.h = 0;
	title.x = title.y = title.w = title.h = 0;
	button1.x = button1.y = button1.w = button1.h = 0;
	button2.x = button2.y = button2.w = button2.h = 0;

	button1_is_hover = button2_is_hover = false;
}
Menu::~Menu()
{
	;
}
void Menu::setText(std::string title_, std::string button1_, std::string button2_)
{
	title_text = title_;
	button1_text = button1_;
	button2_text = button2_;
}
void Menu::setFontSize(int title_, int button_)
{
	title_size = title_;
	button_size = button_;
}
void Menu::setRect(
	int title_x, int title_y,
	int button1_x, int button1_y,
	int button2_x, int button2_y)
{
	run_bg_rect.x = run_bg_rect.y = 0;
	run_bg_rect.w = SCREEN_WIDTH;
	run_bg_rect.h = SCREEN_HIGHT;

	title.x = title_x;
	title.y = title_y;

	button1.x = button1_x;
	button1.y = button1_y;

	button2.x = button2_x;
	button2.y = button2_y;
}
bool Menu::loadImg(std::string file1, std::string file2, std::string file3, std::string file4, SDL_Renderer* scr)
{
	SDL_Surface* surface = IMG_Load(file1.c_str());
	if (!surface) return false;
	menu_texture = SDL_CreateTextureFromSurface(scr, surface);
	if (!menu_texture) return false;

	SDL_FreeSurface(surface);

	surface = IMG_Load(file2.c_str());
	if (!surface) return false;
	bg_texture = SDL_CreateTextureFromSurface(scr, surface);
	if (!bg_texture) return false;

	SDL_FreeSurface(surface);

	if (file3 != "none")
	{
		surface = IMG_Load(file3.c_str());
		if (!surface) return false;
		run_bg_texture = SDL_CreateTextureFromSurface(scr, surface);
		if (!menu_texture) return false;
	}
	font1 = TTF_OpenFont(file4.c_str(), title_size);
	font2 = TTF_OpenFont(file4.c_str(), button_size);

	if (!font1 || !font2) return false;
	if (title_text != "")
	{
		surface = TTF_RenderText_Solid(font1, title_text.c_str(), YELLOW);
		if (!surface) return false;
		title.w = surface->w;
		title.h = surface->h;
		title_texture = SDL_CreateTextureFromSurface(scr, surface);
		if (!title_texture) return false;
		
		SDL_FreeSurface(surface);
	}

	surface = TTF_RenderText_Solid(font2, button1_text.c_str(), GREEN);
	if (!surface) return false;
	button1.w = surface->w;
	button1.h = surface->h;
	button1_texture = SDL_CreateTextureFromSurface(scr, surface);
	if (!button1_texture) return false;
	
	SDL_FreeSurface(surface);

	if (button2_text != "none")
	{
		surface = TTF_RenderText_Solid(font2, button2_text.c_str(), RED);
		if (!surface) return false;
		button2.w = surface->w;
		button2.h = surface->h;
		button2_texture = SDL_CreateTextureFromSurface(scr, surface);
		if (!button2_texture) return false;
		
		SDL_FreeSurface(surface);
	}

	return true;
}
void Menu::update()
{
	if (run_bg_texture)
	{
		run_bg_rect.x++;
		if (run_bg_rect.x > SCREEN_WIDTH) run_bg_rect.x = 0;
	}
}
void Menu::hover(SDL_Renderer* scr)
{
	//button1
	SDL_Point mouse;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	float x, y;
	SDL_RenderWindowToLogical(scr, mouse.x, mouse.y, &x, &y);
	mouse.x = (int)x;
	mouse.y = (int)y;

	if (button1.x <= mouse.x && mouse.x <= button1.x + button1.w && button1.y <= mouse.y && mouse.y <= button1.y + button1.h)
		button1_is_hover = true;
	else button1_is_hover = false;

	
	// button2
	if (button2_text != "none")
	{
		SDL_GetMouseState(&mouse.x, &mouse.y);
		SDL_RenderWindowToLogical(scr, mouse.x, mouse.y, &x, &y);
		mouse.x = (int)x;
		mouse.y = (int)y;

		if (button2.x <= mouse.x && mouse.x <= button2.x + button2.w && button2.y <= mouse.y && mouse.y <= button2.y + button2.h)
			button2_is_hover = true;
		else button2_is_hover = false;
	}
}
void Menu::render(SDL_Renderer* scr)
{
	SDL_Rect renderquad = { 0, 0, SCREEN_WIDTH, SCREEN_HIGHT };
	SDL_RenderCopy(scr, bg_texture, 0, &renderquad);

	if (run_bg_texture)
	{
		renderquad.w = SCREEN_WIDTH - run_bg_rect.x;
		SDL_RenderCopy(scr, run_bg_texture, &run_bg_rect, &renderquad);

		SDL_Rect run_bg_rect2 = { 0, 0, run_bg_rect.x, SCREEN_HIGHT };
		SDL_Rect renderquad2 = { renderquad.w, 0, run_bg_rect2.w, SCREEN_HIGHT };
		SDL_RenderCopy(scr, run_bg_texture, &run_bg_rect2, &renderquad2);
	}
	renderquad.x = renderquad.y = 0;
	renderquad.w = SCREEN_WIDTH;
	renderquad.h = SCREEN_HIGHT;
		
	SDL_RenderCopy(scr, menu_texture, 0, &renderquad);
	if (title_texture)
		SDL_RenderCopy(scr, title_texture, 0, &title);
	if (button1_is_hover || button2_is_hover)
	{
		SDL_SetRenderDrawColor(scr, 255, 255, 255, 150);
		if (button1_is_hover)
			SDL_RenderFillRect(scr, &button1);
		else SDL_RenderFillRect(scr, &button2);
	}
	SDL_RenderCopy(scr, button1_texture, 0, &button1);
	if (button2_texture)
	{
		SDL_RenderCopy(scr, button2_texture, 0, &button2);
	}
}
void Menu::click(SDL_Renderer* scr, SDL_Event evn, bool& button1_, bool& button2_)
{
	if (evn.type == SDL_MOUSEBUTTONDOWN && evn.button.button == SDL_BUTTON_LEFT)
	{
		//button1
		SDL_Point mouse;
		SDL_GetMouseState(&mouse.x, &mouse.y);
		float x, y;
		SDL_RenderWindowToLogical(scr, mouse.x, mouse.y, &x, &y);
		mouse.x = (int)x;
		mouse.y = (int)y;

		if (button1.x <= mouse.x && mouse.x <= button1.x + button1.w && button1.y <= mouse.y && mouse.y <= button1.y + button1.h)
			button1_ = true;

		// button2
		if (button2_text != "none")
		{
			SDL_GetMouseState(&mouse.x, &mouse.y);
			SDL_RenderWindowToLogical(scr, mouse.x, mouse.y, &x, &y);
			mouse.x = (int)x;
			mouse.y = (int)y;

			if (button2.x <= mouse.x && mouse.x <= button2.x + button2.w && button2.y <= mouse.y && mouse.y <= button2.y + button2.h)
				button2_ = true;
		}
	}
}