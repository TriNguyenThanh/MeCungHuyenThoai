#ifndef MAP_H_
#define MAP_H_

#include "function.h"
#include "BaseObject.h"

struct MapObject {
	BaseObject background;
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
	int currentMap;
public:
	GameMap();
	~GameMap();
	friend void setCurrentMap(GameMap& gm, int x);
	int getCurrentMap();
	bool loadMap(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* des);
	MapObject getMap() { return maplist[currentMap]; }
};

#endif // !MAP_H_