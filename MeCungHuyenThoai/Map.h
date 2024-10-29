#pragma once

#include "function.h"
#include "BaseObject.h"
#include "HiddenObject.h"
#include "ItemObject.h"
#include "ThreadObject.h"

struct MapObject {
	BaseObject background;
	BaseObject descoration;
	BaseObject ground;

	std::vector<Threads*> threads_list;
	std::vector<HiddenObject*> hidden_block_list;
	std::vector<Item*> items_list;
	int tile[MAX_MAP_Y][MAX_MAP_X];     // Mang luu thong tin phan loai cua cac tile
	int x, y;							// Vi tri cua tile hien tai
	int start_x, start_y;				// Vi tri bat dau ve map
	int spawn_x, spawn_y;               // Vi tri spawn nhan vat
};

class GameMap {
private:
	MapObject maplist[6];
	int currentMapIndex;
	bool is_boss_died;
public:
	GameMap();
	~GameMap();
	void setCurrentMap(int x);
	int getCurrentMap() const { return currentMapIndex; }
	bool loadMap(SDL_Renderer* screen);
	void DrawBackMap(SDL_Renderer* des);
	void DrawFrontMap(SDL_Renderer* des);
	void DrawHiddenObject(SDL_Renderer* des);
	void clear();
	//void DrawItem(SDL_Renderer* des);
	void update(SDL_Rect mainChar_position, SDL_Renderer* scr);
	MapObject getMap() { return maplist[currentMapIndex]; }
};