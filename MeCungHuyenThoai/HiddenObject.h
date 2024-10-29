#pragma once

#include "function.h"
#include "BaseObject.h"

class HiddenObject : public BaseObject
{
protected:
	SDL_Texture* hidden_texture;
	SDL_Texture* show_texture;
	std::string name;
	bool harm;
	int status;
	int time;
	int period_time;
	int angle;
	SDL_RendererFlip flip;
public:
	HiddenObject();
	virtual ~HiddenObject();
	void set(bool harm_, int status_, int time_, int period_time_);
	void setAngle(int angle_) { angle = angle_; }
	void setFlip(SDL_RendererFlip flip_) { flip = flip_; }
	void chanceStatus() { status = ((status == SHOW) ? HIDDEN : SHOW); }
	bool isHarm() const { return harm; }
	bool is_at(const int& x, const int& y) { return ((x == rect_.x / TILE_SIZE) && (y == rect_.y / TILE_SIZE)); }
	bool is_X_from_a_to_b(const int& a, const int& b) { return (a <= rect_.x && rect_.x <= b); }
	bool is_show() const { return status == SHOW; }
	bool is_static() const { return period_time == 0; }
	bool loadImg(std::string hidden_path, std::string show_path, SDL_Renderer* scr);
	void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	virtual void update();

	int getStatus() const { return status; }
};

class ThornBlock : public HiddenObject
{
public:
	ThornBlock();
	~ThornBlock();
	void update();
};

class RockBlock : public HiddenObject
{
public:
	RockBlock() { ; }
	~RockBlock() { ; }
};