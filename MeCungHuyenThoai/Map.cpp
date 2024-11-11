#include "Map.h"

GameMap::GameMap() {
	currentMapIndex = 1;
	is_boss_died = false;
}
GameMap::~GameMap() {

}
bool GameMap::loadMap(SDL_Renderer* scr) {

	char file_name[40];
	for (int i = 0; i < 6; ++i) {

		// load background layer
		sprintf_s(file_name, "assets\\map\\map0%d\\bg%02d.png", i, i);
		bool ret = maplist[i].background.loadImg(file_name, scr);
		if (ret == false) return false;
		maplist[i].start_x = 0;
		maplist[i].start_y = 0;
		maplist[i].background.setRect(maplist[i].start_x, maplist[i].start_y);

		// load descoration layer
		sprintf_s(file_name, "assets\\map\\map0%d\\desco%02d.png", i, i);
		ret = maplist[i].descoration.loadImg(file_name, scr);
		if (ret == false) return false;
		maplist[i].descoration.setRect(maplist[i].start_x, maplist[i].start_y);

		// load ground layer
		sprintf_s(file_name, "assets\\map\\map0%d\\ground%02d.png", i, i);
		ret = maplist[i].ground.loadImg(file_name, scr);
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

		std::string hidden_rock = "assets\\envairoment\\hidden_rock.png";
		std::string show_rock = "assets\\envairoment\\show_rock.png";
		std::string hidden_thorn = "assets\\envairoment\\hidden_thorn.png";
		std::string show_thorn = "assets\\envairoment\\show_thorn.png";

		for (const auto& block : jsonData["HiddenBlock"])
		{
			HiddenObject* tmp = nullptr;
			if (block["name"] == "thorn")
			{
				tmp = new ThornBlock;
				tmp->loadImg(hidden_thorn, show_thorn, scr);
			}
			else
			{
				tmp = new RockBlock;
				tmp->loadImg(hidden_rock, show_rock, scr);
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

		for (const auto& block : jsonData["items"])
		{
			Item* tmp = new Item;
			std::string name = block["name"];
			if (name == "mana_bottle")
			{
				tmp->loadImg("assets\\item\\mana.png", scr);
			}
			else
			{
				sprintf_s(file_name, "assets\\item\\%s.png", name.c_str());
				bool ret = tmp->loadImg(file_name, scr);
				if (!ret) return false;
			}
			tmp->setRect(block["x"] * TILE_SIZE, block["y"] * TILE_SIZE);
			tmp->setName(name);

			maplist[i].items_list.push_back(tmp);
		}

		for (const auto& mob : jsonData["threads"])
		{
			bool ret = true;
			std::string name = mob["name"];
			std::string dragon = "dragon";
			Threads* thread = nullptr;
			if (name == dragon)
			{
				thread = new Boss;
				thread->setHP(mob["maxHP"]);
				thread->setHeal(mob["heal"]);
				thread->setShield(mob["shield"]);
			}
			else
				thread = new Threads;
			thread->setName(name);
			bool move_ = mob["move"];
			bool fire_ = mob["fire"];
			thread->setMove(move_);
			thread->setFire(fire_);
			if (mob.contains("target"))
			{
				std::string target_type = mob["target"];
				thread->setTarget(target_type);
			}
			if (name == "cobren")
			{
				thread->setFrame(12);
				thread->setFireDelay(50);
				ret = thread->loadImg("assets\\enermies\\cobren.png", scr,
					"assets\\enermies\\cobren_attack.png");
			}
			else if (name == "bat")
			{
				thread->setFrame(9);
				ret = thread->loadImg("assets\\enermies\\bat.png", scr);
			}
			else if (name == "goblin")
			{
				thread->setFrame(8);
				ret = thread->loadImg("assets\\enermies\\goblin.png", scr);
			}
			else if (name == "dragon")
			{
				thread->setFrame(9);
				thread->setFireDelay(30);
				ret = thread->loadImg("assets\\enermies\\dragon.png", scr,
					"assets\\enermies\\dragon_attack.png");
			}
			if (!ret) return false;
			thread->setClip();
			if (move_)
			{
				std::string dir = mob["dir"];
				if (dir == "down") thread->setMoveDir(DOWN);
				else if (dir == "up") thread->setMoveDir(UP);
				else if (dir == "right") thread->setMoveDir(RIGHT);
				else if (dir == "left") thread->setMoveDir(LEFT);
				thread->setDes(mob["x_des"] * TILE_SIZE, mob["y_des"] * TILE_SIZE);
			}

			thread->setSpawn(mob["x"] * TILE_SIZE, mob["y"] * TILE_SIZE);
			thread->spawn();
			thread->setRect(mob["x"] * TILE_SIZE, mob["y"] * TILE_SIZE);
			maplist[i].threads_list.push_back(thread);
		}
	}
	return true;
}
void GameMap::clear()
{
	setCurrentMap(1);
	is_boss_died = false;
	for (int i = 0; i < 6; ++i)
	{
		maplist[i].background.free();
		maplist[i].descoration.free();
		maplist[i].ground.free();

		maplist[i].threads_list.clear();
		maplist[i].hidden_block_list.clear();
		maplist[i].items_list.clear();
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
	for (const auto& item_ : maplist[currentMapIndex].items_list)
	{
		item_->render(des);
	}
	maplist[currentMapIndex].ground.render(des, NULL);

}
void GameMap::setCurrentMap(int x) {
	currentMapIndex = x;
}
void GameMap::DrawHiddenObject(SDL_Renderer* des)
{
	for (const auto& i : maplist[currentMapIndex].threads_list)
	{
		i->render(des);
	}
	for (const auto& i : maplist[currentMapIndex].hidden_block_list)
	{
		i->render(des);
	}
}
void GameMap::update(SDL_Rect mainChar_position, SDL_Renderer* scr) {
	if (!is_boss_died)
	{
		for (const auto& i : maplist[5].threads_list)
		{
			Boss* boss = dynamic_cast<Boss*>(i);
			if (boss)
			{
				if (boss->isLive() == false)
				{
					is_boss_died = true;
					for (int i = 0; i < 6; ++i)
					{
						for (auto& thread : maplist[i].threads_list)
						{
							delete thread;
							thread = nullptr;
						}
						maplist[i].threads_list.clear();
					}
				}
			}
		}
	}
	for (const auto& i : maplist[currentMapIndex].threads_list) i->update(mainChar_position, scr);
	for (const auto& i : maplist[currentMapIndex].hidden_block_list)
	{
		i->update();
		if (is_boss_died && i->is_X_from_a_to_b(20 * TILE_SIZE, 23 * TILE_SIZE) && i->getStatus() == HIDDEN && currentMapIndex == 5)
		{
			i->chanceStatus();
		}
	}
}