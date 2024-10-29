#include "FpsControl.h"

Timer::Timer() {
	frame = frame_count = 0;
	begin_tick = 0;
	end_tick = 0;
	old_tick = 0;
	new_tick = 0;
	font = nullptr;
	texture = nullptr;
	rect_.x = rect_.y = rect_.w = rect_.h = 0;
}
Timer::~Timer() {

}
void Timer::begin()
{
	begin_tick = SDL_GetTicks();
}
void Timer::end()
{
	end_tick = SDL_GetTicks();
}
void Timer::lockFPS(int fps_)
{
	Uint32 real_time = end_tick - begin_tick;
	Uint32 frame_time = 1000 / fps_;

	if (real_time < frame_time)
		SDL_Delay(frame_time - real_time);
}
void Timer::start_count()
{
	font = TTF_OpenFont(UTM_Khuccamta.c_str(), 20);
	old_tick = SDL_GetTicks();
}
void Timer::drawFPS(SDL_Renderer* scr)
{
	new_tick = SDL_GetTicks();
	frame_count++;
	if (new_tick - old_tick >= 1000)
	{
		frame = frame_count;
		frame_count = 0;
		char str[9];
		sprintf_s(str, "FPS: %d", frame);
		SDL_Surface* surface = TTF_RenderText_Solid(font, str, GREEN);
		texture = SDL_CreateTextureFromSurface(scr, surface);

		rect_.x = rect_.y = 10;
		rect_.w = surface->w;
		rect_.h = surface->h;
		old_tick = new_tick;
		SDL_FreeSurface(surface);
	}
	SDL_RenderCopy(scr, texture, nullptr, &rect_);
}