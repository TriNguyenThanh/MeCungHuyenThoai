#include "Map.h"

GameMap::GameMap() {
	currentMapIndex = 1;
}
GameMap::~GameMap() {

}
bool GameMap::loadMap(SDL_Renderer* screen) {
	char file_name[40];
	for (int i = 0; i < 3; ++i) {

		sprintf_s(file_name, "assets\\map\\map0%d\\bg0%d - Copy.png", i, i);
		bool ret = maplist[i].background.loadImg(file_name, screen);
		if (ret == false) return false;
		maplist[i].start_x = 0;
		maplist[i].start_y = 0;
		maplist[i].background.setRect(maplist[i].start_x, maplist[i].start_y);

		FILE* ptr = nullptr;
		sprintf_s(file_name, "assets\\map\\map0%d\\map0%d.dat", i, i);
		fopen_s(&ptr, file_name, "r");
		if (ptr == nullptr) return false;
		for (int y = 0; y < MAX_MAP_Y; ++y) {
			for (int x = 0; x < MAX_MAP_X; ++x) {
				fscanf_s(ptr, "%d", &maplist[i].tile[y][x]);
			}
		}
		fscanf_s(ptr, "%d%d", &maplist[i].spawn_x, &maplist[i].spawn_y);
		fclose(ptr);
	}
}
void GameMap::DrawMap(SDL_Renderer* des) {
	maplist[currentMapIndex].background.render(des, NULL);
}
void GameMap::setCurrentMap(int x) {
	currentMapIndex = x;
}
int GameMap::getCurrentMap() {
	return currentMapIndex;
}