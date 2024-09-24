#ifndef MAIN_ONJECT_H_
#define MINA_OBJECT_H_

#include "function.h"
#include "BaseObject.h"

class MainObject : public BaseObject {
private:
	int status;
	InputType input_type;

	int x_val;
	int y_val;

	int x_pos;
	int y_pos;
	bool on_ground;

	int frame;
	SDL_Rect frame_clip[];

};

#endif 
