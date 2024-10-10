#include "FpsControl.h"

Timer::Timer() {
	tick = 0;
}
Timer::~Timer() {

}
int Timer::get_tick() {

	return tick;
}
void Timer::start() {
	tick = SDL_GetTicks();
}