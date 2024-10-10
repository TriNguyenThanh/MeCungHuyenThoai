#include "Map.h"

GameMap::GameMap() {
	currentMapIndex = 1;
}
GameMap::~GameMap() {

}
bool GameMap::loadMap(SDL_Renderer* screen) {
	char file_name[40];
	for (int i = 0; i < 6; ++i) {

		// load background layer
		sprintf_s(file_name, "assets\\map\\map0%d\\bg%02d.png", i, i);
		bool ret = maplist[i].background.loadImg(file_name, screen);
		if (ret == false) return false;
		maplist[i].start_x = 0;
		maplist[i].start_y = 0;
		maplist[i].background.setRect(maplist[i].start_x, maplist[i].start_y);

		// load descoration layer
		sprintf_s(file_name, "assets\\map\\map0%d\\desco%02d.png", i, i);
		ret = maplist[i].descoration.loadImg(file_name, screen);
		if (ret == false) return false;
		maplist[i].descoration.setRect(maplist[i].start_x, maplist[i].start_y);

		// load ground layer
		sprintf_s(file_name, "assets\\map\\map0%d\\ground%02d.png", i, i);
		ret = maplist[i].ground.loadImg(file_name, screen);
		if (ret == false) return false;
		maplist[i].ground.setRect(maplist[i].start_x, maplist[i].start_y);

		// load tile map
		FILE* ptr = nullptr;
		sprintf_s(file_name, "assets\\map\\map0%d\\map%02d.dat", i, i);
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
// ve back ground
void GameMap::DrawBackMap(SDL_Renderer* des) {
	maplist[currentMapIndex].background.render(des, NULL);
	maplist[currentMapIndex].descoration.render(des, NULL);
}

// ve ground
void GameMap::DrawFrontMap(SDL_Renderer* des)
{
	maplist[currentMapIndex].ground.render(des, NULL);
}
void GameMap::setCurrentMap(int x) {
	currentMapIndex = x;
}
int GameMap::getCurrentMap() {
	return currentMapIndex;
}