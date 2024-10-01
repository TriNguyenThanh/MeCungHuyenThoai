#include "MainObject.h"

// Ham khoi tao nhan vat
MainObject::MainObject() {
	status = RIGHT;

	x_spawn = y_spawn = 0;

	x_val = 0;
	y_val = 0;

	x_pos = 0;
	y_pos = 0;
	on_ground = false;

	int frame = CHAR_FRAME;
	int frame_width = 0;
	int frame_hight = 0;

	input_type.right = input_type.left = input_type.jump = input_type.shoot = 0;
	on_ground = false;
}
// ham huy nhan vat
MainObject::~MainObject() {

}
bool MainObject::loadImg(std::string filepath, SDL_Renderer* scr) {
	bool ret = BaseObject::loadImg(filepath, scr);
	if (ret == true) {
		// lay gia tri cho khung frame cua nhan vat
		frame_width = (rect_.w / CHAR_FRAME) - (25*2);
		frame_hight = rect_.h;
	}
	return ret;
}

void MainObject::setClip() { // tao ra cac khung hinh chuyen dong cho nhan vat
	if (frame_width > 0 && frame_hight > 0) {
		for (int i = 0; i < CHAR_FRAME; ++i) {
			frame_clip[i].x = 25 + (frame_width + 25 * 2) * i;
			frame_clip[i].y = 0;
			frame_clip[i].w = frame_width;
			frame_clip[i].h = frame_hight;
		}
	}
}

void MainObject::show(SDL_Renderer* scr) { // Hien thi nhan vat
	if (status == LEFT) {
		loadImg("assets\\player\\sky\\run_left - Copy.png", scr);
	}
	else if (status == RIGHT)
		loadImg("assets\\player\\sky\\run_right - Copy.png", scr);
	
	if (input_type.left == 1 || input_type.right == 1)
		frame++;
	else
		frame = 0;
	if (frame > 31) frame = 0;
	SDL_Rect* current_frame = &frame_clip[frame/4];
	rect_.x = x_pos;
	rect_.y = y_pos;
	SDL_Rect renderQuad = { rect_.x, rect_.y + 5, frame_width, frame_hight-10};

	SDL_RenderCopy(scr, object_, current_frame, &renderQuad);
}
void MainObject::setSpawn(int x, int y) { // dat vi tri hoi sinh cho nhan vat
	x_pos = rect_.x = x_spawn = x;
	y_pos = rect_.y = y_spawn = y;
}

void MainObject::getInput(SDL_Event evn, SDL_Renderer* scr) { // ham bat su kien nguoi dung
	if (evn.type == SDL_KEYDOWN) {
		switch (evn.key.keysym.sym) {
		case SDLK_d:
			if (status != RIGHT) {
				status = RIGHT;
				loadImg("assets\\player\\sky\\run_right - Copy.png", scr);
			}
			input_type.right = 1;
			input_type.left = 0;
			break;
		case SDLK_a:
			if (status != LEFT) {
				status = LEFT;
				loadImg("assets\\player\\sky\\run_left - Copy.png", scr);
			}
			input_type.right = 0;
			input_type.left = 1;
			break;
		case SDLK_SPACE:
			input_type.jump = 1;
			break;
		}
	}
	if (evn.type == SDL_KEYUP) {
		switch (evn.key.keysym.sym)
		{
		case SDLK_d:
			input_type.right = 0;
			break;
		case SDLK_a:
			input_type.left = 0;
			break;
		case SDLK_SPACE:
			input_type.jump = 0;
			break;
		}
	}
}
void MainObject::movePlayer(GameMap &game_map) {
	x_val = 0;
	y_val += GRAVITY; // Nhan vat luon chiu tac dung cua trong luc nen y_val += gravity

	if (input_type.right == 1) {
		x_val = PLAYER_SPEED; // nhan vat di sang phai thi tang x
	}
	else if (input_type.left == 1) {
		x_val = - PLAYER_SPEED; // nhan vat di sang trai thi giam x
	}
	if (input_type.jump == 1) {
		if (on_ground == true) {
			y_val = - PLAYER_JUMP; // nhan vat nhay thi tang do cao cho nhan vat
		}
		on_ground = false;
		input_type.jump = 0; // nhan vat chi nhay duoc 1 lan nen cho jump = 0
	}
	checkHit(game_map); // kiem tra va cham
	//if (x_pos < 0) {
	//	setCurrentMap(game_map.getCurrentMap - 1);
	//}
}
void MainObject::checkHit(GameMap& game_map) {
	MapObject mapData = game_map.getMap();
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	
	x1 = (x_pos / TILE_SIZE);
	x2 = (x_pos + frame_width - 2) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + frame_hight - 1) / TILE_SIZE;

	// kiem tra va cham tren duoi
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val < 0) {
			if ((mapData.tile[y1][x1] != 0 || mapData.tile[y1][x2] != 0) && (mapData.tile[y1][x1] != 2 && mapData.tile[y1][x2] != 2)) {
				y_val = 0;
			}
		}
		else if (y_val > 0) {
			if (mapData.tile[y2][x1] != 0 || mapData.tile[y2][x2] != 0) {
				y_val = 0;
				on_ground = true;
			}
		}
	}
	// kiem tra va cham hai ben
	x1 = (x_pos + x_val)/TILE_SIZE;
	x2 = (x_pos + x_val + frame_width - 2) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + frame_hight - 1) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val > 0) {
			if ((mapData.tile[y1][x2] != 0 || mapData.tile[y2][x2] != 0) && mapData.tile[y1][x2] != 2) {
				x_val = 0;
				x_pos = (x1 * TILE_SIZE) - x_val;
			}
		}
		else if (x_val < 0) {
			if ((mapData.tile[y1][x1] != 0 || mapData.tile[y2][x1] != 0) && mapData.tile[y1][x1] != 2) {
				x_val = 0;
				x_pos = ((x1 + 1) * TILE_SIZE) + x_val;
			}
		}
	}

	x_pos += x_val;
	y_pos += y_val;
	//if (x_pos < 0 || x_pos + frame_width >= MAX_MAP_X * TILE_SIZE || y_pos + frame_hight > MAX_MAP_Y * TILE_SIZE) {
	//	x_val = 0;
	//	y_val = 0;
	//	x_pos = mapData.spawn_x * TILE_SIZE;
	//	y_pos = mapData.spawn_y * TILE_SIZE;
	//}
	if (x_pos < 0) {
		game_map.setCurrentMap(game_map.getCurrentMap() - 1);
		this->setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
	}
	else if (x_pos + frame_hight > (MAX_MAP_X + 1) * TILE_SIZE) {
		game_map.setCurrentMap(game_map.getCurrentMap() + 1);
		this->setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
	}
}