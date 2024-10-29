#pragma once

#include "function.h"

class Timer {
public:
	Timer();
	~Timer();
	void begin();
	void end();
	void lockFPS(int fps_);
	void start_count();
	void drawFPS(SDL_Renderer* scr);
private:
	Uint32 begin_tick;
	Uint32 end_tick;

	TTF_Font* font;
	SDL_Rect rect_;
	SDL_Texture* texture;
	int frame_count;
	int frame;
	Uint32 old_tick;
	Uint32 new_tick;
};