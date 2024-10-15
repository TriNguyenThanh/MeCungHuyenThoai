#pragma once

#include "function.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void setRect(int x, int y);
	SDL_Rect getRect();
	SDL_Texture* getObject();
	virtual bool loadImg(std::string filepath, SDL_Renderer* screen);
	virtual void render(SDL_Renderer* des, const SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();

protected:
	SDL_Texture* object_;
	SDL_Rect rect_;
};