#ifndef MAIN_ONJECT_H_
#define MINA_OBJECT_H_

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

	int countBullet;

	int frame;
	int frame_width;
	int frame_hight;
	SDL_Rect frame_clip[8];

	std::vector<Bullet*> bullet_list;
public:
	MainObject();
	~MainObject();

	bool loadImg(std::string filepath, SDL_Renderer* scr);
	void updateImg();
	void setSpawn(int x, int y);
	void show(SDL_Renderer* scr);
	void setClip();
	void getInput(SDL_Event evn, SDL_Renderer *scr);
	void movePlayer(GameMap& game_map);
	void moveBullet(GameMap& game_map, SDL_Renderer* scr);
	void checkHit(GameMap& game_map);
};

#endif 
