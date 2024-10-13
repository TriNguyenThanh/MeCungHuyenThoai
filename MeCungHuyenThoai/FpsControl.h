#pragma once

#include "function.h"

class Timer {
public:
	Timer();
	~Timer();
	int get_tick();
	void startGame();
	void pauseGame();
	void unpauseGame();
	void stopGame();
private:
	int start_tick;
	int pause_tick;
	bool game_start;
	bool game_pause;
};
