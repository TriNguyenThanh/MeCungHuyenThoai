#pragma once

#include "function.h"
#include "BaseObject.h"

class Item: public BaseObject
{
private:
	int status;
	std::string name;
public:
	Item();
	~Item();
	void render(SDL_Renderer* scr);
	void setName(std::string name_) { name = name_; }
	bool is_name(std::string name_) const { return name == name_; }
	bool is_at(const int& x, const int& y) { return rect_.x == x * TILE_SIZE && rect_.y == y * TILE_SIZE; }
	bool is_show() const { return status == SHOW; }
	void loot() { status = HIDDEN; }
	void reset() { status = SHOW; }
	void setStatus(int status_) { status = status_; }
};