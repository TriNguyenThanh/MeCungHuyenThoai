#pragma once

#include "function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "Map.h"

class MainObject : public BaseObject {
private:
	int status;
	InputType input_type;

	int x_spawn;
	int y_spawn;

	float x_val;
	float y_val;

	int x_pos;
	int y_pos;

	bool on_ground;
	int dash;

	bool died;
	int respawn;

	int countBullet;

	SDL_Texture* idle = nullptr;
	SDL_Texture* run = nullptr;
	SDL_Texture* jump = nullptr;

	int frame;
	int frame_width;
	int frame_hight;
	SDL_Rect frame_clip[CHAR_FRAME];

	std::vector<Bullet*> bullet_list;
public:
	MainObject();
	~MainObject();

	bool loadImg(std::string filepath, SDL_Renderer* scr);
	bool loadAction(SDL_Renderer* scr, std::string idle_filepath, std::string run_filepath, std::string jump_filepath);
	void updateImg(SDL_Texture* action);
	void setSpawn(int x, int y);
	bool getDied() { return died; }
	void setDiedToFalse() { died = false; }
	void show(SDL_Renderer* scr);
	void setClip();
	void getInput(SDL_Event evn, SDL_Renderer *scr);
	void movePlayer(GameMap& game_map);
	void moveBullet(GameMap& game_map, SDL_Renderer* scr);
	void checkHit(GameMap& game_map);
};