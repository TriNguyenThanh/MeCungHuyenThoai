#include "HiddenObject.h"

HiddenObject::HiddenObject()
{
	hidden_texture = nullptr;
	show_texture = nullptr;
	name = "none";
	harm = false;
	time = 0;
	period_time = 0;
	status = HIDDEN;
	angle = 0;
	flip = SDL_FLIP_NONE;
}
HiddenObject::~HiddenObject()
{

}
void HiddenObject::set(bool harm_, int status_, int time_, int period_time_)
{
	harm = harm_;
	if (status_ == 0)
		status = HIDDEN;
	else status = SHOW;
	period_time = period_time_;
	if (status == SHOW)
		time = period_time / 2;
	else
		time = 0;
	
}
void HiddenObject::update()
{
	if (period_time == 0)
	{
		if (status == SHOW) object_ = show_texture;
		else object_ = hidden_texture;
		return;
	}
	if (status == SHOW)
	{
		time--;
	}
	else
	{
		time++;
	}

	if (time == 0)
	{
		status = HIDDEN;
		object_ = hidden_texture;
	}
	else if (time == period_time / 2)
	{
		status = SHOW;
		object_ = show_texture;
	}
}
bool HiddenObject::loadImg(std::string hidden_path, std::string show_path, SDL_Renderer* scr)
{
	hidden_texture = IMG_LoadTexture(scr, hidden_path.c_str());
	SDL_Surface* surface = IMG_Load(show_path.c_str());
	if (surface != nullptr)
	{
		show_texture = SDL_CreateTextureFromSurface(scr, surface);
		rect_.w = surface->w;
		rect_.h = surface->h;
	}
	SDL_FreeSurface(surface);
	
	object_ = show_texture;

	return object_ != NULL;
}
void HiddenObject::render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, TILE_SIZE, TILE_SIZE };
	SDL_RenderCopyEx(des, object_, clip, &renderquad, angle, NULL, flip);
}
ThornBlock::ThornBlock() {

}
ThornBlock::~ThornBlock()
{

}
void ThornBlock::update() {
	HiddenObject::update();
	if (status == SHOW)
		harm = true;
	else harm = false;
}
//bool HiddenObject::checkHit(const SDL_Rect& targetRect)
//{	
//	int x1 = targetRect.x;
//	int x2 = targetRect.x + targetRect.w;
//	int y1 = targetRect.y;
//	int y2 = targetRect.y + targetRect.h;
//
//	if (
//		is_in(x1, y1, rect_) ||
//		is_in(x1, y2, rect_) ||
//		is_in(x2, y1, rect_) ||
//		is_in(x2, y2, rect_)
//		)
//		return true;
//	return false;
//}