#include "StatusBar.h"

LifeStatus::LifeStatus()
{
	count = 0;
	font = nullptr;
	icon = text = nullptr;
	icon_rect.x = icon_rect.y = icon_rect.w = icon_rect.h = 0;
	text_rect.x = text_rect.y = text_rect.w = text_rect.h = 0;
	rect.x = rect.y = rect.w = rect.h = 0;

}
LifeStatus::~LifeStatus()
{

}
// load hinh anh cho icon sinh mang va so luong sinh mang con lai
bool LifeStatus::loadIcon(std::string filepath, SDL_Renderer* scr)
{
	SDL_Texture* new_icon = nullptr;
	SDL_Texture* new_text = nullptr;
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (surface == nullptr) return false;

	SDL_SetColorKey(surface, SDL_TRUE, BACKGROUND_COLOR);
	new_icon = SDL_CreateTextureFromSurface(scr, surface);
	if (new_icon == nullptr) return false;

	icon_rect.w = TILE_SIZE;
	icon_rect.h = TILE_SIZE;
	
	char str[7];
	sprintf_s(str, "x %d", count);
	surface = TTF_RenderText_Solid(font, str, WHITE);
	if (surface == nullptr) return false;

	new_text = SDL_CreateTextureFromSurface(scr, surface);
	if (new_text == nullptr) return false;
	
	text_rect.w = surface->w;
	text_rect.h = surface->h;

	rect.w = TILE_SIZE * 3;
	rect.h = TILE_SIZE;

	SDL_FreeSurface(surface);
	icon = new_icon;
	text = new_text;

	return true;
}
// cap nhat lai so luong sinh mang
void LifeStatus::update(const int& life_, SDL_Renderer* scr)
{
	if (count != life_)
	{
		count = life_;
		char str[7];
		sprintf_s(str, "x %d", count);
		SDL_Surface* surface = TTF_RenderText_Solid(font, str, WHITE);
		if (surface == nullptr) return;

		text_rect.w = surface->w;
		text_rect.h = surface->h;

		SDL_DestroyTexture(text);
		text = SDL_CreateTextureFromSurface(scr, surface);

		SDL_FreeSurface(surface);
	}
}
// ve so luong sinh mang len man hinh
void LifeStatus::render(SDL_Renderer* scr)
{
	SDL_Rect renderquad = { rect.x, rect.y, TILE_SIZE, TILE_SIZE };
	SDL_RenderCopy(scr, icon, nullptr, &renderquad);

	text_rect.x = rect.x + TILE_SIZE;
	text_rect.y = rect.y;
	SDL_RenderCopy(scr, text,nullptr , &text_rect);
}
void LifeStatus::setRect(const int& x, const int& y)
{
	rect.x = x;
	rect.y = y;

	icon_rect.x = rect.x + 10;
	text_rect.x = icon_rect.x + TILE_SIZE;
}

// dinh nghia crystal status
CrystalStatus::CrystalStatus()
{
	rect.x = rect.y = rect.w = rect.h = 0;
	background = NULL;
	for (int i = 0; i < 5; ++i)
	{
		crystal_status.push_back(0);
	}
}
CrystalStatus::~CrystalStatus()
{

}
bool CrystalStatus::loadImg(SDL_Renderer* scr)
{
	// background
	SDL_Surface* surface = IMG_Load("assets\\screen\\statusbar\\crystal.png");
	if (surface == NULL) return false;
	rect.w = surface->w;
	rect.h = surface->h;
	background = SDL_CreateTextureFromSurface(scr, surface);

	// blue crystal
	bool ret = crystal_object[0].loadImg("assets\\screen\\statusbar\\blue_mana_crystal.png", scr);
	if (ret == false) return ret;
	
	// green crystal
	ret = crystal_object[1].loadImg("assets\\screen\\statusbar\\green_mana_crystal.png", scr);
	if (ret == false) return ret;
	
	// light blue crystal
	ret = crystal_object[2].loadImg("assets\\screen\\statusbar\\light_blue_mana_crystal.png", scr);
	if (ret == false) return ret;

	// red crystal
	ret = crystal_object[3].loadImg("assets\\screen\\statusbar\\red_mana_crystal.png", scr);
	if (ret == false) return ret;

	// violet crystal
	ret = crystal_object[4].loadImg("assets\\screen\\statusbar\\violet_mana_crystal.png", scr);
	if (ret == false) return ret;

	SDL_FreeSurface(surface);

	return true;
}
void CrystalStatus::setRect(const int& x, const int& y)
{
	rect.x = x;
	rect.y = y;
	crystal_object[0].setRect(rect.x, rect.y);
	crystal_object[1].setRect(rect.x + TILE_SIZE, rect.y);
	crystal_object[2].setRect(rect.x + TILE_SIZE * 2, rect.y);
	crystal_object[3].setRect(rect.x + TILE_SIZE * 3, rect.y);
	crystal_object[4].setRect(rect.x + TILE_SIZE * 4, rect.y);
}
void CrystalStatus::render(SDL_Renderer* scr)
{
	SDL_Rect renderquad = { rect.x, rect.y, TILE_SIZE * 5, TILE_SIZE };
	SDL_Point mouse;
	SDL_GetMouseState(&mouse.x, &mouse.y);

	if (rect.x <= mouse.x && mouse.x <= rect.x + TILE_SIZE && rect.y <= mouse.y && mouse.y <= rect.y + TILE_SIZE)
	{
		SDL_SetRenderDrawColor(scr, 195, 195, 195, 255);
		SDL_RenderFillRect(scr, &renderquad);
	}

	SDL_RenderCopy(scr, background, nullptr, &renderquad);
	for (int i = 0; i < 5; ++i)
	{
		SDL_Texture* render_texture = crystal_object[i].getObject();
		SDL_Rect renderquad = { crystal_object[i].getRect().x , crystal_object[i].getRect().y, TILE_SIZE, TILE_SIZE};
		SDL_SetTextureAlphaMod(render_texture, crystal_status[i]);
		SDL_RenderCopy(scr, render_texture, nullptr, &renderquad);
	}
}
void CrystalStatus::update(std::vector<int> crystal_status_, SDL_Renderer* scr)
{
	for (int i = 0; i < 5; ++i)
	{
		crystal_status[i] = crystal_status_[i];
	}
}

// dinh nghia mini map
MiniMap::MiniMap()
{
	current_map = 1;
	cover = 0;
	rect.x = rect.y = rect.w = rect.h = 0;
	for (int i = 0; i < 6; ++i)
	{
		map[i].x = map[i].y = 0;
		map[i].w = TILE_SIZE;
		map[i].h = TILE_SIZE / 2;
	}
}
MiniMap::~MiniMap()
{

}
bool MiniMap::loadMap(SDL_Renderer* scr, std::string cover_path)
{
	SDL_Surface* surface = IMG_Load(cover_path.c_str());
	if (surface == nullptr) return false;
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_SetColorKey(surface, SDL_TRUE, BACKGROUND_COLOR);
	cover = SDL_CreateTextureFromSurface(scr, surface);

	return true;
}
void MiniMap::setRect(const int& x, const int &y)
{
	rect.x = x;
	rect.y = y;

	map[3].x = map[0].x = rect.x;
	map[4].x = map[1].x = rect.x + TILE_SIZE;
	map[5].x = map[2].x = rect.x + TILE_SIZE * 2;

	map[0].y = map[1].y = map[2].y = rect.y;
	map[3].y = map[4].y = map[5].y = rect.y + TILE_SIZE / 2;
}
void MiniMap::update(int current_map_)
{
	current_map = current_map_;
}
void MiniMap::render(SDL_Renderer* scr)
{
	for (int i = 0; i < 6; ++i)
	{
		if (i == current_map)
		{
			SDL_SetRenderDrawColor(scr, 255, 255, 255, 255);
		}
		else
		{
			SDL_SetRenderDrawColor(scr, 255, 255, 255, 0);
		}
		SDL_RenderFillRect(scr, &map[i]);
	}
	SDL_RenderCopy(scr, cover, nullptr, &rect);
}

// dinh nghia quit button
void QuitButton::getInput(SDL_Renderer* scr, SDL_Event evn, bool &quit)
{
	if (evn.type == SDL_MOUSEBUTTONDOWN && evn.button.button == SDL_BUTTON_LEFT)
	{
		SDL_Point mouse;
		SDL_GetMouseState(&mouse.x, &mouse.y);
		float x, y;
		SDL_RenderWindowToLogical(scr, mouse.x, mouse.y, &x, &y);
		mouse.x = x;
		mouse.y = y;

		std::cout << mouse.x << ' ' << mouse.y << '\n';
		std::cout << rect_.x << ' ' << rect_.y << '\n';
		if (rect_.x <= mouse.x && mouse.x <= rect_.x + TILE_SIZE && rect_.y <= mouse.y && mouse.y <= rect_.y + TILE_SIZE)
		{
			quit = true;
		}
	}
}
void QuitButton::render(SDL_Renderer* scr)
{
	SDL_Point mouse;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	float x, y;
	SDL_RenderWindowToLogical(scr, mouse.x, mouse.y, &x, &y);
	mouse.x = x;
	mouse.y = y;
	SDL_Rect renderquad = { rect_.x, rect_.y, TILE_SIZE, TILE_SIZE };

	if (rect_.x <= mouse.x && mouse.x <= rect_.x + TILE_SIZE && rect_.y <= mouse.y && mouse.y <= rect_.y + TILE_SIZE)
	{
		SDL_SetRenderDrawColor(scr, 195, 195, 195, 255);
		SDL_RenderFillRect(scr, &renderquad);
	}
	SDL_RenderCopy(scr, object_, nullptr, &renderquad);
}

// dinh nghia status bar
StatusBar::StatusBar()
{
	text_size = 0;
	font = nullptr;
	rect.x = rect.y = 0;
	rect.w = 768;
	rect.h = 48;
	life = 3;
	mana = 0;
	for (int i = 0; i < 5; ++i)
	{
		crystal.push_back(0);
	}
	current_map = 1;
	is_quit = false;
	background = nullptr;
	LifeBorder = nullptr;
	ManaBorder = nullptr;
	CrystalBorder = nullptr;
	mini_map = nullptr;
	QuitStatus = nullptr;
}
StatusBar::~StatusBar()
{

}
void StatusBar::setRect(const int& x, const int& y)
{
	rect.x = x;
	rect.y = y;

	LifeBorder->setRect(rect.x + 10, rect.y + 5);
	ManaBorder->setRect(rect.x + TILE_SIZE * 3 + 10, rect.y + 5);
	CrystalBorder->setRect(rect.x + TILE_SIZE * 6 + 10, rect.y + 5);
	mini_map->setRect(rect.x + TILE_SIZE * 12 + 10, rect.y + 5);
}

bool StatusBar::loadimg(SDL_Renderer* scr,std::string background_path, std::string life_icon_path, std::string mana_icon_path, std::string minimap_cover_path, std::string quit_icon_path)
{
	JSON jsonData;
	std::ifstream file("assets\\screen\\statusbar\\statusbar.json");
	if (!file) return false;
	
	file >> jsonData;
	file.close();

	rect.x = jsonData["x"]; rect.y = jsonData["y"]; rect.h = jsonData["h"]; rect.w = jsonData["w"];
	text_size = jsonData["text_size"];
	font = TTF_OpenFont(UTM_Khuccamta.c_str(), text_size);

	SDL_Surface* surface = IMG_Load(background_path.c_str());
	if (surface == NULL) return false;
	SDL_SetColorKey(surface, SDL_TRUE, BACKGROUND_COLOR);
	background = SDL_CreateTextureFromSurface(scr, surface);
	if (background == nullptr) return false;
	SDL_FreeSurface(surface);

	bool ret = true;
	// load chi so sinh mang
	LifeBorder = new LifeStatus;
	if (LifeBorder == nullptr) return false;
	
	LifeBorder->setFont(font);
	ret = LifeBorder->loadIcon(life_icon_path, scr);
	if (!ret) return false;
	LifeBorder->setRect(rect.x, rect.y);

	// load chi so mana
	ManaBorder = new ManaStatus;
	if (ManaBorder == nullptr) return false;

	ManaBorder->setFont(font);
	ret = ManaBorder->loadIcon(mana_icon_path, scr);
	if (!ret) return false;
	ManaBorder->setRect(rect.x + TILE_SIZE * 6, rect.y);

	// load trang thai cac crystal
	CrystalBorder = new CrystalStatus;
	if (CrystalBorder == nullptr) return false;

	ret = CrystalBorder->loadImg(scr);
	if (!ret) return false;
	CrystalBorder->setRect(rect.x + TILE_SIZE * 12, rect.y);


	// load mini map
	mini_map = new MiniMap;
	if (mini_map == nullptr) return false;

	ret = mini_map->loadMap(scr, minimap_cover_path);
	if (!ret) return false;
	mini_map->setRect(rect.x + TILE_SIZE * 21, rect.y);

	// load quit button
	QuitStatus = new QuitButton;
	if (QuitStatus == NULL) return false;

	ret = QuitStatus->loadImg(quit_icon_path, scr);
	if (!ret) return false;

	QuitStatus->setRect(rect.x + TILE_SIZE * 28, rect.y);
	return true;
}
void StatusBar::update(SDL_Renderer* scr,MainObject& mainChar,GameMap& game_map)
{
	life = mainChar.getLife();
	mana = mainChar.getMana();
	crystal = mainChar.getcrystal();
	current_map = game_map.getCurrentMap();

	LifeBorder->update(life, scr);
	ManaBorder->update(mana, scr);
	CrystalBorder->update(crystal, scr);
	mini_map->update(current_map);
	
}
void StatusBar::render(SDL_Renderer* scr)
{
	SDL_SetTextureAlphaMod(background, 100);
	SDL_RenderCopy(scr, background, nullptr, &rect);
	SDL_SetRenderDrawColor(scr, 180, 180, 180, 255);
	LifeBorder->render(scr);
	ManaBorder->render(scr);
	CrystalBorder->render(scr);
	mini_map->render(scr);
	QuitStatus->render(scr);
}
void StatusBar::setCrystal(std::vector<int> crystal_)
{
	for (int i = 0; i < 5; ++i)
	{
		crystal[i] = crystal_[i];
	}
}
void StatusBar::getInput(SDL_Renderer* scr, SDL_Event evn, bool &quit)
{
	QuitStatus->getInput(scr, evn, quit);
}