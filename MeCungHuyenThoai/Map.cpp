#include "Map.h"

GameMap::GameMap() {
	currentMapIndex = 1;
}
GameMap::~GameMap() {

}
bool GameMap::loadMap(SDL_Renderer* screen) {
	std::string hidden_rock = "assets\\envairoment\\hidden_rock.png";
	std::string show_rock = "assets\\envairoment\\show_rock.png";
	std::string hidden_thorn = "assets\\envairoment\\hidden_thorn.png";
	std::string show_thorn = "assets\\envairoment\\show_thorn.png";

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
		sprintf_s(file_name, "assets\\map\\map0%d\\map%02d.dat", i, i);
		std::ifstream file_tilemap(file_name);
		if (!file_tilemap) return false;
		for (int y = 0; y < MAX_MAP_Y; ++y) {
			for (int x = 0; x < MAX_MAP_X; ++x) {
				file_tilemap >> maplist[i].tile[y][x];
			}
		}
		file_tilemap.close();

		// load file json
		sprintf_s(file_name, "assets\\map\\map0%d\\map%02d.json", i, i);
		std::ifstream file_json(file_name);
		if (!file_json) return false;
		JSON jsonData;
		file_json >> jsonData;
		file_json.close();

		maplist[i].spawn_x = jsonData["spawn"]["x"];
		maplist[i].spawn_y = jsonData["spawn"]["y"];

		for (const auto& block : jsonData["HiddenBlock"])
		{
			HiddenObject* tmp = nullptr;
			if (block["name"] == "thorn")
			{
				tmp = new ThornBlock;
				tmp->loadImg(hidden_thorn, show_thorn, screen);
			}
			else
			{
				tmp = new RockBlock;
				tmp->loadImg(hidden_rock, show_rock, screen);
			}
			tmp->setRect(block["x"] * TILE_SIZE, block["y"] * TILE_SIZE);
			tmp->set(block["harm"], block["status"], block["time"], block["period_time"]);

			if (block.contains("angle")) tmp->setAngle(block["angle"]);
			if (block.contains("flip"))
			{
				if (block["flip"] == "HORIZONE") tmp->setFlip(SDL_FLIP_HORIZONTAL);
				else tmp->setFlip(SDL_FLIP_VERTICAL);
			}
			maplist[i].hidden_block_list.push_back(tmp);
		}
	}
	return true;
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
void GameMap::DrawHiddenObject(SDL_Renderer* des)
{
	for (const auto& i : maplist[currentMapIndex].hidden_block_list)
	{
		i->render(des);
	}
}
void GameMap::UpdateHiddenObject() {
	for (const auto& i : maplist[currentMapIndex].hidden_block_list)
	{
		i->update();
	}
}