#ifndef MAP_H_
#define MAP_H_

#include "function.h"
#include "BaseObject.h"

struct MapObject {
	BaseObject background;
	BaseObject descoration;
	BaseObject ground;
	int tile[MAX_MAP_Y][MAX_MAP_X];     // Mang luu thong tin phan loai cua cac tile
	int x, y;							// Vi tri cua tile hien tai
	int start_x, start_y;				// Vi tri bat dau ve map
	int spawn_x, spawn_y;               // Vi tri spawn nhan vat

	std::string filepath;
};

class GameMap {
private:
	std::vector <BaseObject> Object;
	MapObject maplist[6];
	int currentMapIndex;
public:
	GameMap();
	~GameMap();
	void setCurrentMap(int x);
	int getCurrentMap();
	bool loadMap(SDL_Renderer* screen);
	void DrawBackMap(SDL_Renderer* des);
	void DrawFrontMap(SDL_Renderer* des);
	MapObject getMap() { return maplist[currentMapIndex]; }
};

#endif // !MAP_H_