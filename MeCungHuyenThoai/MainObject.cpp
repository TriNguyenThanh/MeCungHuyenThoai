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
	dash = 0;

	died = false;

	countBullet = 5;

	int frame = CHAR_FRAME;
	int frame_width = 0;
	int frame_hight = 0;

	input_type.right = input_type.left = input_type.jump = input_type.shoot = input_type.interact = 0;
	on_ground = false;
}
// ham huy nhan vat
MainObject::~MainObject() {

}
// load hinh anh cho nhan vat
bool MainObject::loadImg(std::string filepath, SDL_Renderer* scr) {
	bool ret = BaseObject::loadImg(filepath, scr);
	if (ret == true) {
		// lay gia tri cho khung frame cua nhan vat
		frame_width = rect_.w / CHAR_FRAME;
		frame_hight = rect_.h;
	}
	frame_width = rect_.w / CHAR_FRAME;
	frame_hight = rect_.h;
	return ret;
}
// load hinh anh cho cac chuyen dong
bool MainObject::loadAction(SDL_Renderer* scr, std::string idle_filepath, std::string run_filepath, std::string jump_filepath)
{
	SDL_Surface* surface = nullptr;

	surface = IMG_Load(idle_filepath.c_str());
	if (surface == nullptr) return false;
	idle = SDL_CreateTextureFromSurface(scr, surface);

	surface = IMG_Load(jump_filepath.c_str());
	if (surface == nullptr) return false;
	jump = SDL_CreateTextureFromSurface(scr, surface);

	surface = IMG_Load(run_filepath.c_str());
	if (surface == nullptr) return false;
	run = SDL_CreateTextureFromSurface(scr, surface);

	return true;
}
void MainObject::updateImg(SDL_Texture* action)
{
	object_ = action;
}
void MainObject::setClip() { // tao ra cac khung hinh chuyen dong cho nhan vat
	if (frame_width > 0 && frame_hight > 0) {
		for (int i = 0; i < CHAR_FRAME; ++i) {
			frame_clip[i].x = frame_width * i;
			frame_clip[i].y = 0;
			frame_clip[i].w = frame_width;
			frame_clip[i].h = frame_hight;
		}
	}
}
void MainObject::show(SDL_Renderer* scr) { // Hien thi nhan vat
	
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (status == LEFT) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	
	int tmp = 0;
	frame++;

	if (!on_ground)
	{
		if (frame > 13)
		{
			frame = 14;
		}
		tmp = frame / 4;
	}
	else if (frame > 39)
	{
		frame = 0;
		input_type.shoot = 0;
		tmp = 0;
	}
	else
	{
		tmp = frame / 2;
	}

	double angle = 0;
	if (died == true)
	{
		angle = 90;
		died = false;
		frame = 0;
		x_pos = x_spawn;
		y_pos = y_spawn;
	}
	else if (input_type.left == 1 || input_type.right == 1)
	{
		if (tmp >= 12)
			angle = 10;
	}
	if (input_type.left == 1)
		angle = -angle;

	SDL_Rect* current_frame = &frame_clip[tmp];	
	SDL_Rect renderQuad = { rect_.x, rect_.y, frame_width, frame_hight};
	SDL_RenderCopyEx(scr, object_, current_frame, &renderQuad, angle, nullptr, flip);
	rect_.x = x_pos;
	rect_.y = y_pos;
}
void MainObject::setSpawn(int x, int y) { // dat vi tri hoi sinh cho nhan vat
	rect_.x = x_spawn = x;
	rect_.y = y_spawn = y;
	if (x_pos == 0 && y_pos == 0)
	{
		x_pos = rect_.x;
		y_pos = rect_.y;
	}
}

void MainObject::getInput(SDL_Event evn, SDL_Renderer* scr) { // ham bat su kien nguoi dung
	if (evn.type == SDL_KEYDOWN) {
		switch (evn.key.keysym.sym) {
		case SDLK_j:
			if (countBullet > 0 && input_type.shoot == 0)
			{
				input_type.shoot == 1;
				// vien dan
				Bullet* playerBullet = new Bullet;
				playerBullet->loadImg("assets\\player\\bullet\\blue.png", scr);

				if (status == LEFT)
				{
					// dat huong trai cho vien dan
					playerBullet->setDir(LEFT);
					playerBullet->setRect(this->x_pos, this->y_pos + 40);
				}
				else
				{
					// dat huong phai cho vien dan
					playerBullet->setDir(RIGHT);
					playerBullet->setRect(this->x_pos + this->frame_width - FRAME_SPACE, this->y_pos + 40);
				}
				// cho phep vien dan di chuyen

				playerBullet->setMove(1);
				countBullet--;

				playerBullet->setXY_val(BULLET_SPEED, BULLET_SPEED);
				// them vien dan vao list
				bullet_list.push_back(playerBullet);
			}
			break;
		case SDLK_LSHIFT:
			dash = 2;
			break;
		case SDLK_w:
			input_type.climb = 1;
			break;
		case SDLK_f:
			input_type.interact = 1;
			break;
		case SDLK_d:
			if (status != RIGHT) {
				status = RIGHT;
			}
			if (object_ != run) 
				updateImg(run);
			input_type.right = 1;
			input_type.left = 0;
			break;
		case SDLK_a:
			if (status != LEFT) {
				status = LEFT;
			}
			if (object_ != run)
				updateImg(run);
			input_type.right = 0;
			input_type.left = 1;
			break;
		case SDLK_SPACE:
			input_type.jump = 1;
			if (object_ != jump) updateImg(jump);
			break;
		case SDLK_k:
			countBullet = 5;
			break;
		}
	}
	else if (evn.type == SDL_KEYUP) {
		switch (evn.key.keysym.sym)
		{
		case SDLK_LSHIFT:
			dash = 0;
			break;
		case SDLK_w:
			input_type.climb = 0;
			break;
		case SDLK_f:
			input_type.interact = 0;
			break;
		case SDLK_d:
			input_type.right = 0;
			updateImg(idle);
			break;
		case SDLK_a:
			input_type.left = 0;
			updateImg(idle);
			break;
		}
	}
}
void MainObject::moveBullet(GameMap& game_map, SDL_Renderer* scr)
{
	for (int i = 0; i < bullet_list.size(); ++i)
	{
		Bullet* playerBullet = bullet_list.at(i);
		if (playerBullet != nullptr)
		{
			if (playerBullet->getMove() == 1)
			{
				SDL_RendererFlip flip = SDL_FLIP_NONE;
				if (status == LEFT) flip = SDL_FLIP_HORIZONTAL;
				playerBullet->move(game_map);
				playerBullet->render(scr, nullptr, flip);
			}
			else
			{
				bullet_list.erase(bullet_list.begin() + i);
				if (playerBullet != NULL)
				{
					delete playerBullet;
					playerBullet = nullptr;
				}
			}
		}

	}
}
void MainObject::movePlayer(GameMap &game_map) {
	if (died == true) return;

	x_val = 0;
	y_val += GRAVITY; // Nhan vat luon chiu tac dung cua trong luc nen y_val += gravity
	if (y_val > PLAYER_MAX_FALL_SPEED) y_val = PLAYER_MAX_FALL_SPEED;

	if (input_type.right == 1) {
		x_val = (PLAYER_SPEED + dash); // nhan vat di sang phai thi tang x
	}
	else if (input_type.left == 1) {
		x_val = -(PLAYER_SPEED + dash); // nhan vat di sang trai thi giam x
	}
	if (input_type.jump == 1) {
		if (on_ground == true) {
			y_val = -(PLAYER_JUMP + dash); // nhan vat nhay thi tang do cao cho nhan vat
		}
		on_ground = false;
		input_type.jump = 0; // nhan vat chi nhay duoc 1 lan nen cho jump = 0
	}
	checkHit(game_map); // kiem tra va cham
}
void MainObject::checkHit(GameMap& game_map) {
	MapObject mapData = game_map.getMap();
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	
	x1 = (x_pos + FRAME_SPACE) / TILE_SIZE;
	x2 = (x_pos + frame_width - FRAME_SPACE) / TILE_SIZE;

	y1 = (y_pos + 25 + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + frame_hight - 1) / TILE_SIZE;

	// kiem tra va cham tren duoi
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if ((mapData.tile[y1][x1] == 2 || mapData.tile[y1][x2] == 2) && input_type.climb == 1)
			y_val = -PLAYER_CLIMB;

		if (y_val < 0) {
			if (mapData.tile[y1][x1] == 3 || mapData.tile[y1][x2] == 3)
			{
				died = true;
				on_ground = false;
				return;
			}

			if ((mapData.tile[y1][x1] != 0 || mapData.tile[y1][x2] != 0) && (mapData.tile[y1][x1] != 2 && mapData.tile[y1][x2] != 2)) {
				y_val = 0;
			}
		}
		else if (y_val > 0) {
			if (mapData.tile[y2][x1] == 3 && mapData.tile[y2][x2] == 3)
			{
				died = true;
				on_ground = false;
				return;
			}
			if ((mapData.tile[y2][x1] != 0 || mapData.tile[y2][x2] != 0) && (mapData.tile[y2][x1] != 2 && mapData.tile[y2][x2] != 2)) {
				y_val = 0;
				on_ground = true;
				if (object_ == jump)
				{
					if (input_type.left == 1 || input_type.right == 1)
						updateImg(run);
					else
						updateImg(idle);
				}
			}
		}
	}
	// kiem tra va cham hai ben
	x1 = (x_pos + x_val +  FRAME_SPACE)/TILE_SIZE;
	x2 = (x_pos + x_val +  frame_width - FRAME_SPACE) / TILE_SIZE;

	y1 = (y_pos + 25) / TILE_SIZE;
	y2 = (y_pos + frame_hight - 1) / TILE_SIZE;
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val > 0) {
			if ((mapData.tile[y1][x2] != 0 || mapData.tile[y2][x2] != 0) && (mapData.tile[y1][x2] != 2 && mapData.tile[y2][x2] != 2)) {
				x_val = 0;
				x_pos = (x1 * TILE_SIZE) - x_val - FRAME_SPACE;
			}
		}
		else if (x_val < 0) {
			if ((mapData.tile[y1][x1] != 0 || mapData.tile[y2][x1] != 0) && (mapData.tile[y1][x1] != 2 && mapData.tile[y2][x1] != 2)) {
				x_val = 0;
				x_pos = ((x1 + 1) * TILE_SIZE) + x_val - FRAME_SPACE;
			}
		}
	}

	x_pos += x_val;
	y_pos += y_val;

	if ((x_pos + (FRAME_SPACE / 4 * 3)) < 0) {
		game_map.setCurrentMap(game_map.getCurrentMap() - 1);
		this->setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
		x_pos = MAX_MAP_X * TILE_SIZE - frame_width;
	}
	else if ((x_pos + frame_width - (FRAME_SPACE / 4 * 3)) > MAX_MAP_X * TILE_SIZE) {
		game_map.setCurrentMap(game_map.getCurrentMap() + 1);
		this->setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
		x_pos = 10;
	}
	else if (y_pos + 25 > SCREEN_HIGHT)
	{
		game_map.setCurrentMap(game_map.getCurrentMap() + 3);
		this->setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
		y_pos = 10;
	}
	else if (y_pos + 25 < 0)
	{
		game_map.setCurrentMap(game_map.getCurrentMap() - 3);
		this->setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
		y_pos = MAX_MAP_Y * TILE_SIZE - frame_hight;
	}
}