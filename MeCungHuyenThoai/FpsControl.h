#ifndef FPS_CONTROL_H_
#define FPS_CONTROL_H_

#include "function.h"

class Timer {
public:
	Timer();
	~Timer();
	int get_tick();
	void start();
private:
	int tick;
};

#endif // !FPS_CONTROL_H_
