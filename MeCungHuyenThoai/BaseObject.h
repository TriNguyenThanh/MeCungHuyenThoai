#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

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
	void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void free();

private:
	SDL_Texture* object_;
	SDL_Rect rect_;
};

#endif // !BASE_OBJECT_H_
