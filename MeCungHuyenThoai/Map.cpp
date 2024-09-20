#include "Map.h"

GameMap::GameMap() {
	currentMap = 0;
}
GameMap::~GameMap() {

}
bool GameMap::loadMap(SDL_Renderer* screen) {
	char file_name[30];
	for (int i = 0; i < 2; ++i) {

		sprintf_s(file_name, "assets\\map\\bg0%d.png", i + 1);
		bool ret = maplist[i].background.loadImg(file_name, screen);
		if (ret == false) return false;
		maplist[i].start_x = 0;
		maplist[i].start_y = 0;
		maplist[i].background.setRect(maplist[i].start_x, maplist[i].start_y);

		FILE* ptr = nullptr;
		fopen_s(&ptr, "assets\\map\\map01.dat", "r");
		if (ptr == nullptr) return false;
		for (int y = 0; y < MAX_MAP_Y; ++y) {
			for (int x = 0; x < MAX_MAP_X; ++x) {
				fscanf_s(ptr, "%d", &maplist[i].tile[y][x]);
			}
		}
	}
}
void GameMap::DrawMap(SDL_Renderer* des) {
	maplist[currentMap].background.render(des, NULL);
}
void GameMap::setCurrentMap(int x) {
	currentMap = x;
}
int GameMap::getCurrentMap() {
	return currentMap;
}