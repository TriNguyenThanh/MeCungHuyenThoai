#pragma once

#include "function.h"
#include "BaseObject.h"
#include "Map.h"

class Bullet : public BaseObject {
private:
	int x_val;
	int y_val;

	int is_move;
	int dir;
public:
	Bullet();
	~Bullet();

	void render(SDL_Renderer* scr);

	void setXY_val(int x, int y) { x_val = x; y_val = y; }
	int getX_val() { return x_val; }
	int getY_val() { return y_val; }

	void setDir(int dir) { this->dir = dir; }
	int getDir() const { return dir; }
	void setMove(const int& x) { is_move = x; }
	int getMove() { return is_move; }

	void move(GameMap& game_map);
	void checkHit(GameMap& game_map);
};
