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