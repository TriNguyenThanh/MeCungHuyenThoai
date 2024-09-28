#ifndef MAIN_ONJECT_H_
#define MINA_OBJECT_H_

#include "function.h"
#include "BaseObject.h"
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

	int frame;
	int frame_width;
	int frame_hight;
	SDL_Rect frame_clip[8];
public:
	MainObject();
	~MainObject();

	enum walk_type {
		LEFT = -1,
		RIGHT = 1
	};

	bool loadImg(std::string filepath, SDL_Renderer* scr);
	void updateImg();
	void setSpawn(int x, int y);
	void show(SDL_Renderer* scr);
	void setClip();
	void getInput(SDL_Event evn, SDL_Renderer *scr);
	void movePlayer(MapObject &mapData);
	void checkHit(MapObject &mapData);
};

#endif 
