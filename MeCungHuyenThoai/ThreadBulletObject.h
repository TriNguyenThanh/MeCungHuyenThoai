#pragma once

#include "function.h"

class ThreadBullet {
public:
	ThreadBullet();
	~ThreadBullet();
	bool loadImg(std::string filepath, SDL_Renderer* scr);
	void setName(std::string name_) { name = name_; }
	void setRect(const int& x, const int& y);
	void setDes(const int& x, const int& y);
	void setMove(bool move_);
	
	void render(SDL_Renderer* scr);
	void move_bullet();
	bool checkHit(int tile_map[MAX_MAP_Y][MAX_MAP_X], SDL_Rect rect_); // kiem tra va cham voi nhan vat

	SDL_Rect getRect() const { return rect; } // tra ve khung rect cua vien dan
	bool move() const { return is_move; } // kiem tra vien dan con ton tai hay khong
private:
	std::string name;

	SDL_Rect rect;
	SDL_Texture* texture;

	int x_pos;
	int y_pos;

	int x_des;
	int y_des;

	float x_val;
	float y_val;

	bool is_move;

	int dir;
	
	float angle;
};