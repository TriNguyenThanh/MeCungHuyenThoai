#include "FpsControl.h"

Timer::Timer() {
	start_tick = 0;
	pause_tick = 0;
	game_pause = false;
	game_start = true;
}
Timer::~Timer() {

}
int Timer::get_tick() {

	return start_tick;
}
void Timer::startGame() {
	game_pause = false;
	game_start = true;
	start_tick = SDL_GetTicks();
}
void Timer::pauseGame() {
	if (game_start == true && game_pause == false)
	game_pause = true;
	pause_tick = SDL_GetTicks() - start_tick;
}
void Timer::unpauseGame()
{
	if (game_pause == true)
	{
		game_pause = false;
	}
}
void Timer::stopGame()
{
	start_tick = 0;
	pause_tick = 0;
	game_pause = false;
	game_start = false;
}