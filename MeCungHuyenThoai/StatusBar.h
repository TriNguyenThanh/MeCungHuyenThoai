#pragma once
#include "function.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Map.h"

class LifeStatus
{
private:
	int count;
	TTF_Font* font;
	SDL_Texture* icon;
	SDL_Texture* text;
	SDL_Rect icon_rect;
	SDL_Rect text_rect;
	SDL_Rect rect;
public:
	LifeStatus();
	~LifeStatus();
	bool loadIcon(std::string filepath, SDL_Renderer* scr);
	void setRect(const int& x, const int& y);
	void render(SDL_Renderer* scr);
	void update(const int& life_, SDL_Renderer* scr);
	void setFont(TTF_Font* font_) { font = font_; }
};

class ManaStatus : public LifeStatus
{
public:
	ManaStatus() { ; }
	~ManaStatus() { ; }
};

class CrystalStatus
{
public:
	CrystalStatus();
	~CrystalStatus();
	bool loadImg(SDL_Renderer* scr);
	void setRect(const int& x, const int& y);
	void render(SDL_Renderer* scr);
	void update(std::vector<int> crystal_status_, SDL_Renderer* scr);
private:
	SDL_Rect rect;
	std::vector<int> crystal_status;
	SDL_Texture* background;
	BaseObject crystal_object[5];
};

class MiniMap
{
private:
	int current_map;
	SDL_Texture* cover;
	SDL_Rect rect;
	SDL_Rect map[6];
public:
	MiniMap();
	~MiniMap();
	bool loadMap(SDL_Renderer* scr, std::string cover_path);
	void update(int current_map_);
	void setRect(const int& x, const int& y);
	void render(SDL_Renderer* scr);
};

class QuitButton : public BaseObject
{
public:
	QuitButton() { ; }
	~QuitButton() { ; }

	void getInput(SDL_Renderer* scr, SDL_Event evn, bool &quit);
	void render(SDL_Renderer* scr);
};

class StatusBar
{
private:
	int text_size;
	TTF_Font* font;
	SDL_Texture* background;
	SDL_Rect rect;

	int life;
	LifeStatus* LifeBorder;

	int mana;
	ManaStatus* ManaBorder;

	std::vector<int> crystal;
	CrystalStatus* CrystalBorder;

	int current_map;
	MiniMap* mini_map;

	bool is_quit;
	QuitButton* QuitStatus;

public:
	StatusBar();
	~StatusBar();
	bool loadimg(SDL_Renderer* scr, std::string background_path, std::string life_icon_path, std::string mana_icon_path, std::string minimap_cover_path, std::string quit_icon_path);
	void setRect(const int& x, const int& y);
	void update(SDL_Renderer* scr, MainObject& mainChar, GameMap& game_map);
	void render(SDL_Renderer* scr);

	void setLife(const int& x) { life = x; }
	void setMana(const int& x) { mana = x; }
	void setCrystal(std::vector<int> crystal_);
	void setCurrentMap(int x) { current_map = x; }

	int getLife() { return life; }
	int getMana() { return mana; }
	void getInput(SDL_Renderer* scr, SDL_Event evn, bool &quit);
	//
};