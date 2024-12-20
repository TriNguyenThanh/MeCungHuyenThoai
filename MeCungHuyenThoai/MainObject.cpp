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

	life = 6;
	shield = 0;
	countMana = 0;

	died = false;
	respawn = RESPAWN_TIME;
	undead = UNDEAD_TIME;
	

	frame = CHAR_FRAME;
	frame_width = 0;
	frame_hight = 0;
	for (int i = 0; i < frame; ++i)	{

		frame_clip[i].x = frame_clip[i].y = frame_clip[i].w = frame_clip[i].h = 0;
	}

	for (int i = 0; i < 5; ++i)
	{
		crystal.push_back(0);
		spawn_crystal.push_back(0);
	}

	input_type.right = input_type.left = input_type.jump = input_type.shoot = input_type.interact = 0;
	on_ground = false;
}
// ham huy nhan vat
MainObject::~MainObject() {

}
void MainObject::reset()
{
	x_pos = x_spawn;
	y_pos = y_spawn;
	respawn = RESPAWN_TIME;
	for (auto& i : bullet_list)
	{
		i->setMove(0);
	}
	countMana = 0;
	life = 6;
	shield = 0;
	dash = 0;
	on_ground = false;
	status = RIGHT;
	for (int i = 0; i < 5; i++)
	{
		crystal[i] = spawn_crystal[i] = 0;
	}
}
void MainObject::setToWin()
{
	for (int i = 0; i < 4; i++)
	{
		crystal[i] = spawn_crystal[i] = 255;
	}
}
void MainObject::setToLose()
{
	life = 0;
	countMana = 0;
	for (int i = 0; i < 5; i++)
	{
		crystal[i] = spawn_crystal[i] = 0;
	}
}
void MainObject::getMoreMana()
{
	countMana += 10;
	shield++;
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

	rect_.w = frame_width - (FRAME_SPACE * 2);
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
void MainObject::show(SDL_Renderer* scr, const SoundEffect& effect) { // Hien thi nhan vat
	
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (status == LEFT) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	
	int tmp = 0;
	frame++;
	undead--;

	if (undead <= 0)
	{
		undead = 0;
		SDL_SetTextureAlphaMod(object_, 255);
	}
	else if (undead > 0)
		SDL_SetTextureAlphaMod(object_, 100);

	if (!on_ground)
	{
		if (frame > 31)
		{
			frame = 14;
		}
		tmp = frame / 4;
	}
	else if (frame > 39)
	{
		frame = 0;
		//input_type.shoot = 0;
		tmp = 0;
	}
	else
	{
		tmp = frame / 2;
	}

	double angle = 0;
	if (died == true)
	{
		if (respawn > (RESPAWN_TIME - 7))
		{
			angle = (3 + (RESPAWN_TIME - respawn) * 2.5);
		}
		else
		{
			angle = 90;
		}
		if (respawn >= 0) 
		{
			respawn--;
		}
		else
		{
			died = false;
			life--;
			if (life < 0)
			{
				;// game over
			}
			frame = 0;
			x_pos = x_spawn;
			y_pos = y_spawn;
			respawn = RESPAWN_TIME;
			undead = UNDEAD_TIME;
		}

	}
	else if (input_type.left == 1 || input_type.right == 1)
	{
		if (tmp % 10 >= 6 && on_ground == true)
		{
			angle = 3;
			effect.playWalk();
		}
	}
	if (input_type.shoot == 1)
	{
		angle = 18;
		//effect.playFire();
	}

	if (status == LEFT)
		angle = -angle;
	SDL_Point point;
	point.x = frame_width / 2;
	point.y = frame_hight;
	SDL_Rect* current_frame = &frame_clip[tmp];	
	SDL_Rect renderQuad = { rect_.x, rect_.y, frame_width, frame_hight};
	SDL_RenderCopyEx(scr, object_, current_frame, &renderQuad, angle, &point, flip);
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
bool MainObject::kill(GameMap& game_map, const SoundEffect& effect)
{
	if (undead > 0) return false;
	if (shield > 0)
	{
		undead = UNDEAD_TIME / 4;
		shield--;
		return false;
	}
	y_val = 0;
	x_val = 0;
	if (died == false)
	{
		died = true;
		effect.playDeath();
	}
	for (int i = 0; i < 5; ++i)
	{
		crystal[i] = spawn_crystal[i];
	}
	for (const auto& item_ : game_map.getMap().items_list)
	{
		if (item_->is_name("blue_mana_crystal"))
		{
			item_->setStatus(255 - crystal[0]);
			break;
		}
		else if (item_->is_name("green_mana_crystal"))
		{
			item_->setStatus(255 - crystal[1]);
			break;
		}
		else if (item_->is_name("light_blue_mana_crystal"))
		{
			item_->setStatus(255 - crystal[2]);
			break;
		}
		else if (item_->is_name("red_mana_crystal"))
		{
			item_->setStatus(255 - crystal[3]);
			break;
		}
		else if (item_->is_name("violet_mana_crystal"))
		{
			item_->setStatus(255 - crystal[4]);
			break;
		}
	}
	return true;
}
void MainObject::getInput(SDL_Event evn, SDL_Renderer* scr, const SoundEffect& effect) { // ham bat su kien nguoi dung
	if (evn.type == SDL_KEYDOWN && died == false) {
		switch (evn.key.keysym.sym) {
		case SDLK_j:
			if (countMana >= BULLET_MANA_TAKE && input_type.shoot == 0)
			{
				input_type.shoot = 1;
				//effect.playFire();
				// vien dan
				Bullet* playerBullet = new Bullet;
				playerBullet->loadImg("assets\\player\\bullet\\orange.png", scr);
				if (input_type.climb == 1)
				{
					playerBullet->setDir(UP);
					playerBullet->setRect(this->x_pos + (FRAME_SPACE / 2), this->y_pos);
				}
				else if (status == LEFT)
				{
					// dat huong trai cho vien dan
					playerBullet->setDir(LEFT);
					playerBullet->setRect(this->x_pos, this->y_pos + 50);
				}
				else if (status == RIGHT)
				{
					// dat huong phai cho vien dan
					playerBullet->setDir(RIGHT);
					playerBullet->setRect(this->x_pos + this->frame_width - FRAME_SPACE, this->y_pos + 50);
				}
				// cho phep vien dan di chuyen

				playerBullet->setMove(1);
				countMana -= BULLET_MANA_TAKE;

				playerBullet->setXY_val(BULLET_SPEED, BULLET_SPEED);
				// them vien dan vao list
				bullet_list.push_back(playerBullet);
			}
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
		}
	}
	else if (evn.type == SDL_KEYUP) {
		switch (evn.key.keysym.sym)
		{
		case SDLK_LSHIFT:
			if (dash == 0) dash = DASH_SPEED;
			else dash = 0;
			break;
		case SDLK_j:
			input_type.shoot = 0;
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
				playerBullet->move(game_map);
				playerBullet->render(scr);
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
void MainObject::movePlayer(GameMap &game_map, const SoundEffect& effect) {
	x_val = 0;
	y_val += (float) GRAVITY; // Nhan vat luon chiu tac dung cua trong luc nen y_val += gravity
	if (y_val > PLAYER_MAX_FALL_SPEED) y_val = (float) PLAYER_MAX_FALL_SPEED;

	if (input_type.right == 1) {
		x_val = (float) (PLAYER_SPEED + dash); // nhan vat di sang phai thi tang x
	}
	else if (input_type.left == 1) {
		x_val = (float) - (PLAYER_SPEED + dash); // nhan vat di sang trai thi giam x
	}
	if (input_type.jump == 1) {
		if (on_ground == true) {
			y_val = (float) - (PLAYER_JUMP + dash); // nhan vat nhay thi tang do cao cho nhan vat
			effect.playJump();
		}
		on_ground = false;
		input_type.jump = 0; // nhan vat chi nhay duoc 1 lan nen cho jump = 0
	}
	if (died == true)
	{
		x_val = 0;
		y_val += (float) GRAVITY;
		if (y_val > PLAYER_MAX_FALL_SPEED) y_val = (float) PLAYER_MAX_FALL_SPEED;
	}
	checkHit(game_map, effect); // kiem tra va cham

	// Cap nhat lai vi tri
	x_pos += (int) roundf(x_val);
	y_pos += (int) roundf(y_val);

	// dich chuyen sang map khac
	int old_map_index = game_map.getCurrentMap();
	if ((x_pos + (FRAME_SPACE / 4 * 3)) < 0) {
		game_map.setCurrentMap(game_map.getCurrentMap() - 1);
		this->setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
		for (int i = 0; i < 5; ++i)
		{
			spawn_crystal[i] = crystal[i];
		}
		x_pos = MAX_MAP_X * TILE_SIZE - frame_width;
	}
	else if ((x_pos + frame_width - (FRAME_SPACE / 4 * 3)) > MAX_MAP_X * TILE_SIZE) {
		game_map.setCurrentMap(game_map.getCurrentMap() + 1);
		this->setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
		for (int i = 0; i < 5; ++i)
		{
			spawn_crystal[i] = crystal[i];
		}
		x_pos = 10;
	}
	else if (y_pos + (frame_hight / 2) > SCREEN_HIGHT)
	{
		game_map.setCurrentMap(game_map.getCurrentMap() + 3);
		this->setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
		for (int i = 0; i < 5; ++i)
		{
			spawn_crystal[i] = crystal[i];
		}
		y_pos = 10;
	}
	else if (y_pos + 25 < 0)
	{
		game_map.setCurrentMap(game_map.getCurrentMap() - 3);
		this->setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
		for (int i = 0; i < 5; ++i)
		{
			spawn_crystal[i] = crystal[i];
		}
		y_pos = MAX_MAP_Y * TILE_SIZE - frame_hight;
	}
	int new_map_index = game_map.getCurrentMap();
	if (new_map_index != old_map_index)
	{
		if (new_map_index == 5 && old_map_index == 4)
		{

			Mix_HaltMusic();
			effect.playBossFight();
			shield += life - 1;
			life = 1;

		}
		else if (old_map_index == 5)
		{
			Mix_HaltMusic();
			effect.playBackground();
		}
	}

}
void MainObject::checkHit(GameMap& game_map, const SoundEffect& effect)
{
	for (auto& i : game_map.getMap().threads_list)
	{
		if (i->isLive())
		{
			if (i->checkRectHit(game_map.getMap().tile, rect_)) // va cham truc tiep voi quai
			{
				if (kill(game_map, effect))
					return;
			}
		}
	}

	MapObject mapData = game_map.getMap();
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;
	
	x1 = (x_pos + FRAME_SPACE) / TILE_SIZE;
	x2 = (x_pos + frame_width - FRAME_SPACE) / TILE_SIZE;

	y1 = (y_pos + 25 + (int) roundf(y_val)) / TILE_SIZE;
	y2 = (y_pos + (int) roundf(y_val) + frame_hight - 1) / TILE_SIZE;

	// kiem tra va cham tren duoi
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		// nhan vat leo day di len
		if ((mapData.tile[y1][x1] == 2 || mapData.tile[y1][x2] == 2) && input_type.climb == 1)
		{
			y_val = -PLAYER_CLIMB;
			if (!Mix_Playing(15))
				effect.playClimb();
		}
		// nhan vat huong len tren
		if (y_val < 0) {
			// va cham voi block

			bool left = (mapData.tile[y1][x1] == 0 || mapData.tile[y1][x1] == 2);
			bool right = (mapData.tile[y1][x2] == 0 || mapData.tile[y1][x2] == 2);
			
			if (!left || !right) {
				// va cham voi block an
				if (mapData.tile[y1][x1] == 4 || mapData.tile[y1][x2] == 4 ||
					mapData.tile[y1][x1] == 5 || mapData.tile[y1][x2] == 5 ||
					mapData.tile[y1][x1] == 7 || mapData.tile[y1][x2] == 7)
				{
					for (const auto& block : game_map.getMap().hidden_block_list)
					{
						if (block->is_at(x1, y1) || block->is_at(x2, y1))
						{
							if (block->isHarm())
							{
								if (kill(game_map, effect))
									return;
							}
							if (block->is_show())
							{
								y_val = 0;
								on_ground = false;
							}
							break;
						}
					}
					
				}
				else if (mapData.tile[y1][x1] == 6 || mapData.tile[y1][x2] == 6)
				{
					for (const auto& item_ : game_map.getMap().items_list)
					{
						if ((item_->is_at(x1, y1) || item_->is_at(x2, y1)) && item_->is_show())
						{
							item_->loot();
							if (item_->is_name("mana_bottle"))
							{
								countMana += MANA_BOTTLE_VALUE1;
								effect.playManaPickUp();
								life++;
							}
							else if (item_->is_name("blue_mana_crystal"))
							{
								crystal[0] = SHOW;
							}
							else if (item_->is_name("green_mana_crystal"))
							{
								crystal[1] = SHOW;
							}
							else if (item_->is_name("light_blue_mana_crystal"))
							{
								crystal[2] = SHOW;
							}
							else if (item_->is_name("red_mana_crystal"))
							{
								crystal[3] = SHOW;
							}
							else if (item_->is_name("violet_mana_crystal"))
							{
								crystal[4] = SHOW;
							}

							break;
						}
					}
				}
				else
				{
					y_val = (float) 0;
				}
				// va cham voi gai tinh
				if (mapData.tile[y1][x1] == 3 || mapData.tile[y1][x2] == 3)
				{
					if (kill(game_map, effect))
						return;
				}
			}
		}
		// nhan vat huong xuong
		else if (y_val > 0) {
			// va cham voi block
			
			bool left = (mapData.tile[y2][x1] == 0 || mapData.tile[y2][x1] == 2);
			bool right = (mapData.tile[y2][x2] == 0 || mapData.tile[y2][x2] == 2);
			if (!left || !right) {
				if (mapData.tile[y2][x1] == 4 || mapData.tile[y2][x2] == 4 ||
					mapData.tile[y2][x1] == 5 || mapData.tile[y2][x2] == 5 ||
					mapData.tile[y2][x1] == 7 || mapData.tile[y2][x2] == 7)
				{
 					for (const auto& block : game_map.getMap().hidden_block_list)
					{
						if (block->is_at(x1, y2) || block->is_at(x2, y2))
						{
							if (block->isHarm())
							{
								if (kill(game_map, effect))
									return;
							}
							if (block->is_show())
							{
								y_pos = y2 * TILE_SIZE - frame_hight - 1;
								y_val = 0;
								if (on_ground == false)
								{
									on_ground = true;
									effect.playLand();
								}
								
								if (object_ == jump)
								{
									if (input_type.left == 1 || input_type.right == 1)
										updateImg(run);
									else
										updateImg(idle);
								}
							}
							break;
						}
					}	
				}
				else if (mapData.tile[y2][x1] == 6 || mapData.tile[y2][x2] == 6)
				{
					for (const auto& block : game_map.getMap().items_list)
					{
						if ((block->is_at(x1, y2) || block->is_at(x2, y2)) && block->is_show())
						{
							block->loot();
							if (block->is_name("mana_bottle"))
							{
								countMana += MANA_BOTTLE_VALUE1;
								life++;
								effect.playManaPickUp();
							}
							else
							{
								effect.playCrystalPickUp();
								if (block->is_name("blue_mana_crystal"))
								{
									crystal[0] = SHOW;
								}
								else if (block->is_name("green_mana_crystal"))
								{
									crystal[1] = SHOW;
								}
								else if (block->is_name("light_blue_mana_crystal"))
								{
									crystal[2] = SHOW;
								}
								else if (block->is_name("red_mana_crystal"))
								{
									crystal[3] = SHOW;
								}
								else if (block->is_name("violet_mana_crystal"))
								{
									crystal[4] = SHOW;
								}
							}
							break;
						}
					}
				}
				else
				{
					y_val = (float) 0;
					if (mapData.tile[y2 - 1][x1] == 5 || mapData.tile[y2 - 1][x2] == 5)
					{
						for (const auto& block : game_map.getMap().hidden_block_list)
						{
							if (block->is_at(x1, y2-1) || block->is_at(x2, y2-1))
								if (block->isHarm())
								{
									if (kill(game_map, effect))
										return;
								}
						}
					}
					if (on_ground == false)
					{
						on_ground = true;
						effect.playLand();
					}
					if (object_ == jump)
					{
						if (input_type.left == 1 || input_type.right == 1)
							updateImg(run);
						else
							updateImg(idle);
					}
				}
				if (mapData.tile[y2][x1] == 3 && mapData.tile[y2][x2] == 3)
				{
					if (kill(game_map, effect))
						return;
				}
			}
		}
	}
	// kiem tra va cham hai ben
	x1 = (x_pos +  FRAME_SPACE + (int) roundf(x_val))/TILE_SIZE;
	x2 = (x_pos +  frame_width - FRAME_SPACE + (int) roundf(x_val)) / TILE_SIZE;

	y1 = (y_pos + 25) / TILE_SIZE;
	y2 = (y_pos + frame_hight - 1) / TILE_SIZE;
	if (input_type.interact == 1) {
		x1 = (x_pos + FRAME_SPACE + (int) roundf(x_val)) / TILE_SIZE;
	}
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		// Nhan vat di qua phai
		if (x_val > 0) {
			bool up = false, down = false;
			if (mapData.tile[y1][x2] == 0 || mapData.tile[y1][x2] == 2 || mapData.tile[y1][x2] == 5 || mapData.tile[y1][x2] == 4) up = true;
			if (mapData.tile[y2][x2] == 0 || mapData.tile[y2][x2] == 2 || mapData.tile[y2][x2] == 5) down = true;

			if (!up || !down)
			{
				if (mapData.tile[y1][x2] == 6 || mapData.tile[y2][x2] == 6)
				{
					for (const auto& block : game_map.getMap().items_list)
					{
						if ((block->is_at(x2, y1) || block->is_at(x2, y2)) && block->is_show())
						{
							block->loot();
							if (block->is_name("mana_bottle"))
							{
								countMana += MANA_BOTTLE_VALUE1;
								effect.playManaPickUp();
								life++;
							}
							else
							{
								effect.playCrystalPickUp();
								if (block->is_name("blue_mana_crystal"))
								{
									crystal[0] = SHOW;
								}
								else if (block->is_name("green_mana_crystal"))
								{
									crystal[1] = SHOW;
								}
								else if (block->is_name("light_blue_mana_crystal"))
								{
									crystal[2] = SHOW;
								}
								else if (block->is_name("red_mana_crystal"))
								{
									crystal[3] = SHOW;
								}
								else if (block->is_name("violet_mana_crystal"))
								{
									crystal[4] = SHOW;
								}
							}
							break;
						}
					}
				}
				else if (mapData.tile[y1][x2] == 4 || mapData.tile[y2][x2] == 4 || mapData.tile[y1][x2] == 7 || mapData.tile[y2][x2] == 7)
				{
					for (const auto& block : game_map.getMap().hidden_block_list)
					{
						if ((block->is_at(x2, y1) || block->is_at(x2, y2)) && block->is_show())
						{
							if (block->isHarm())
							{
								if (kill(game_map, effect))
									return;
							}
							x_val = (float) 0;
							x_pos = (x1 * TILE_SIZE) - (int) roundf(x_val) - FRAME_SPACE;
							break;
						}
					}
				}
				else
				{
					x_val = (float) 0;
					x_pos = (x1 * TILE_SIZE) - (int) roundf(x_val) - FRAME_SPACE;
				}
			}
		}
		// Nhan vat di qua trai
		else if (x_val < 0) {
			bool up = (mapData.tile[y1][x1] == 0 || mapData.tile[y1][x1] == 2 || mapData.tile[y1][x1] == 5 || mapData.tile[y1][x1] == 4);
			bool down = (mapData.tile[y2][x1] == 0 || mapData.tile[y2][x1] == 2 || mapData.tile[y2][x1] == 5);

			if (!up || !down)
			{
				if (mapData.tile[y1][x1] == 6 || mapData.tile[y2][x1] == 6)
				{
					for (const auto& block : game_map.getMap().items_list)
					{
						if ((block->is_at(x1, y1) || block->is_at(x1, y2)) && block->is_show())
						{
							block->loot();
							if (block->is_name("mana_bottle"))
							{
								countMana += MANA_BOTTLE_VALUE1;
								effect.playManaPickUp();
								life++;
							}
							else
							{
								effect.playCrystalPickUp();
								if (block->is_name("blue_mana_crystal"))
								{
									crystal[0] = SHOW;
								}
								else if (block->is_name("green_mana_crystal"))
								{
									crystal[1] = SHOW;
								}
								else if (block->is_name("light_blue_mana_crystal"))
								{
									crystal[2] = SHOW;
								}
								else if (block->is_name("red_mana_crystal"))
								{
									crystal[3] = SHOW;
								}
								else if (block->is_name("violet_mana_crystal"))
								{
									crystal[4] = SHOW;
								}
							}
							break;
						}
					}
				}
				else if (mapData.tile[y1][x1] == 4 || mapData.tile[y2][x1] == 4 || mapData.tile[y1][x1] == 7 || mapData.tile[y2][x1] == 7)
				{
					for (const auto& block : game_map.getMap().hidden_block_list)
					{
						if ((block->is_at(x1, y1) && block->is_show()) || (block->is_at(x1, y2) && block->is_show()))
						{
							if (block->isHarm())
							{
								if (kill(game_map, effect))
									return;
							}
							x_val = (float) 0;
							x_pos = ((x1 + 1) * TILE_SIZE) + (int) roundf(x_val) - FRAME_SPACE;
							break;
						}
					}
				}
				else
				{
					x_val = (float) 0;
					x_pos = ((x1 + 1) * TILE_SIZE) + (int) roundf(x_val) - FRAME_SPACE;
				}
			}
		}
		// nhan vat dung yen
		else
		{
			if (input_type.interact != 1) return;
			for (int i = 0; i < 4; ++i)
			{
				if (crystal[i] == 0) return;
			}

			if (status == LEFT)
				x_val = (float) - (PLAYER_SPEED + dash);
			else x_val = (float) (PLAYER_SPEED + dash);

			x1 = (x_pos + (int) roundf(x_val) + FRAME_SPACE) / TILE_SIZE;
			x2 = (x_pos + (int) roundf(x_val) + frame_width - FRAME_SPACE) / TILE_SIZE;

			y1 = (y_pos + 25) / TILE_SIZE;
			y2 = (y_pos + frame_hight - 1) / TILE_SIZE;

			x_val = (float)0;

			for (const auto& block : game_map.getMap().hidden_block_list)
			{
				if (block->is_at(x2, y1) && block->is_show())
				{
					if (block->is_static() && input_type.interact == 1)
					{
						block->chanceStatus();
					}
				}
				if (block->is_at(x2, y2) && block->is_show())
				{
					if (block->is_static() && input_type.interact == 1)
					{
						block->chanceStatus();
					}
				}
				if (block->is_at(x1, y1) && block->is_show())
				{
					if (block->is_static() && input_type.interact == 1)
					{
						block->chanceStatus();
					}
				}
				if (block->is_at(x1, y2) && block->is_show())
				{

					if (block->is_static() && input_type.interact == 1)
					{
						block->chanceStatus();
					}
				}
			}
			
		}
	}
}