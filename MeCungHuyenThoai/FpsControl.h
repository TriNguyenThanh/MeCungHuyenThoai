#ifndef FPS_CONTROL_H_
#define FPS_CONTROL_H_

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

#endif // !FPS_CONTROL_H_
