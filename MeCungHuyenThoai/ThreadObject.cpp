#include "ThreadObject.h"

Threads::Threads()
{
	name = "none";
	x_spawn = y_spawn = x_des = y_des = 0;
	x_pos = y_pos = 0;
	rect.x = rect.y = rect.w = rect.h = 0;
	frame_width = frame_hight = 0;
	frame = 0;
	frame_count = 0;
	texture = nullptr;
	attack_texture = nullptr;
	idle_texture = nullptr;
	fire = 0;
	fire_delay = 0;
	fire_delay_time = 0;
	x_target = y_target = 0;
	move = 0;
	move_dir = RIGHT;
	dir = RIGHT;
	show = SHOW;
	target = "dynamic";

	for (auto& i : clip)
	{
		i.x = i.y = i.w = i.h = 0;
	}
}
Threads::~Threads()
{
	;
}
bool Threads::loadImg(std::string filepath, SDL_Renderer* scr, std::string filepath2)
{
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (!surface) return false;
	SDL_SetColorKey(surface, SDL_TRUE, BACKGROUND_COLOR);
	frame_width = surface->w / frame_count;
	frame_hight = surface->h;
	idle_texture = SDL_CreateTextureFromSurface(scr, surface);
	if (!idle_texture) return false;

	if (filepath2 != "none" && filepath2 != filepath)
	{
		surface = IMG_Load(filepath2.c_str());
		if (!surface) return false;
		SDL_SetColorKey(surface, SDL_TRUE, BACKGROUND_COLOR);
		frame_width = surface->w / frame_count;
		frame_hight = surface->h;
		attack_texture = SDL_CreateTextureFromSurface(scr, surface);
		if (!attack_texture) return false;
	}
	else if (filepath2 == "none")
	{
		texture = attack_texture = idle_texture;
	}
	SDL_FreeSurface(surface);

	int frame_space = 0;
	if (name == "bat")
		frame_space = 25;
	else if (name == "cobren")
		frame_space = 40;
	else if (name == "goblin")
		frame_space = 29;
	else if (name == "dragon")
		frame_space = 128;
	rect.w = frame_width - (frame_space * 2);
	rect.h = frame_hight;

	return true;
}
void Threads::attack(SDL_Renderer* scr)
{
	if (fire_delay_time == fire_delay + 1)
	{
		fire_delay_time = fire_delay;
		ThreadBullet* thread_bullet = new ThreadBullet;
		std::string file_path = "none";
		std::string name_of_bullet = "none";
		if (name == "cobren")
		{
			file_path = "assets\\enermies\\magma.png";
			name_of_bullet = "magma_ball";
		}
		else if (name == "dragon")
		{
			file_path = "assets\\enermies\\fire.png";
			name_of_bullet = "dragon_fire";
		}
		thread_bullet->loadImg(file_path, scr);
		thread_bullet->setName(name_of_bullet);
		if (dir == LEFT)
			thread_bullet->setRect(x_pos, y_pos + rect.h / 2);
		else if (dir == RIGHT)
			thread_bullet->setRect(x_pos + rect.w, y_pos + rect.h / 2);
		thread_bullet->setDes(x_target, y_target);
		thread_bullet->setMove(true);

		bullet_list.push_back(thread_bullet);
	}
}
void Threads::setFireDelay(int fire_delay_time_)
{
	fire_delay = fire_delay_time_;
	fire_delay_time = random(0, fire_delay-1);
}
void Threads::render(SDL_Renderer* scr)
{
	if (show == HIDDEN) return;
	int tmp = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (dir == RIGHT) flip = SDL_FLIP_HORIZONTAL;
	
	frame++;
	if (frame > frame_count * SLOW_FRAME_RENDER - 1)
	{
		frame = 0;
		tmp = 0;
	}
	else
	{
		tmp = frame / SLOW_FRAME_RENDER;
	}

	SDL_Rect* current_frame = &clip[tmp];
	SDL_Rect renderquad = { rect.x, rect.y, frame_width, frame_hight };
	SDL_RenderCopyEx(scr, texture, current_frame, &renderquad, 0, 0, flip);
	rect.x = x_pos;
	rect.y = y_pos;
}
void Threads::update(SDL_Rect mainChar_position, SDL_Renderer* scr)
{
	if (show == HIDDEN) return;

	x_target = mainChar_position.x + FRAME_SPACE + mainChar_position.w / 2;
	y_target = mainChar_position.y + mainChar_position.h / 2;
	std::string dynamic = "dynamic";
	if (target != dynamic)
		y_target = y_pos + rect.h / 2;

	if (!move || move_dir != LEFT && move_dir != RIGHT)
	{
		if ((mainChar_position.w / CHAR_FRAME / 2 + mainChar_position.x) > rect.x) dir = RIGHT;
		else dir = LEFT;
	}
	if (fire)
	{
		if (fire_delay_time < fire_delay)
		{
			fire_delay_time++;
			if (texture != idle_texture) texture = idle_texture;
		}
		else
		{
			if (texture != attack_texture)
			{
				fire_delay_time = fire_delay + 1;
				texture = attack_texture;
				frame = 1;
			}
			else if (frame / SLOW_FRAME_RENDER == 5)
			{
				attack(scr);
			}

			if (frame == 0)
			{
				fire_delay_time = 0;
				texture = idle_texture;
			}
		}
		for (int i = 0; i < bullet_list.size(); i++)
		{
			ThreadBullet* bullet = bullet_list[i];
			if (bullet->move())
			{
				bullet->move_bullet();
				bullet->render(scr);
			}
			else
			{
				bullet_list.erase(bullet_list.begin() + i);
				if (bullet != nullptr)
				{
					delete bullet;
					bullet = nullptr;
				}
			}
		}

	}
	if (move)
	{
		int speed = 0;
		if (name == "bat")
		{
			speed = BAT_SPEED;
		}
		else if (name == "dragon")
		{
			speed = random(6, 9);
		}
		if (move_dir == DOWN)
			y_pos += speed;
		else if (move_dir == UP)
			y_pos -= speed;
		else if (move_dir == RIGHT)
			x_pos += speed;
		else if (move_dir == LEFT)
			x_pos -= speed;

		if (move_dir == DOWN && y_pos > y_des)
		{
			y_pos = y_des;
			move_dir = UP;
		}
		else if (move_dir == UP && y_pos < y_spawn)
		{
			y_pos = y_spawn;
			move_dir = DOWN;
		}
		else if (move_dir == RIGHT && x_pos > x_des)
		{
			x_pos = x_des;
			move_dir = LEFT;
			dir = LEFT;
		}
		else if (move_dir == LEFT && x_pos < x_spawn)
		{
			x_pos = x_spawn;
			move_dir = RIGHT;
			dir = RIGHT;
		}
	}

}
void Threads::setSpawn(int x, int y)
{
	x_pos = x_spawn = x;
	y_pos = y_spawn = y;

	if (move)
	{
		std::string name_ = name;
		if (move_dir == UP || move_dir == DOWN)
			y_pos = random(y_spawn, y_des);
		if (move_dir == RIGHT || move_dir == LEFT)
			x_pos = random(x_spawn, x_des);
	}
	
}
void Threads::setClip()
{
	for (int i = 0; i < frame_count; ++i)
	{
		clip[i].x = i*frame_width;
		clip[i].y = 0;
		clip[i].w = frame_width;
		clip[i].h = frame_hight;
	}
}
void Threads::setRect(int x, int y)
{
	rect.x = x;
	rect.y = y;
}
bool Threads::checkRectHit(int tile_map[MAX_MAP_Y][MAX_MAP_X], SDL_Rect rect_) // kiem tra nhan vat (rect_) co va cham voi thread va thread_bullet khong
{
	if (show == HIDDEN) return false;
	int frame_space = 0;
	if (name == "bat")
		frame_space = 25;
	else if (name == "cobren")
		frame_space = 40;
	else if (name == "goblin")
		frame_space = 29;
	else if (name == "dragon")
		frame_space = 128;

	int dem = 0;
	if (rect_.x + FRAME_SPACE + 10 + rect_.w < this->rect.x + frame_space || this->rect.x + frame_space + this->rect.w < rect_.x + FRAME_SPACE + 10) dem++;
	if (rect_.y - 35 + rect_.h < this->rect.y || this->rect.y + this->rect.h < rect_.y + 35) dem++;

	if (fire)
	{
		for (auto& thread_bullet : bullet_list)
		{
			if (thread_bullet->checkHit(tile_map, rect_))
			{
				return true;
			}
		}
	}

	if (!dem)
	{
		return true;
	}
	return false;
}
bool Threads::checkBulletHit(const int& x, const int& y) // va cham voi bullet cua nguoi choi
{
	if (show == HIDDEN) return false;
	int frame_space = 0;
	if (name == "bat")
		frame_space = 25;
	else if (name == "cobren")
		frame_space = 10;
	else if (name == "goblin")
		frame_space = 29;
	else if (name == "dragon")
		frame_space = 128;

	if (rect.x + frame_space <= x && x <= rect.x + frame_space + rect.w && rect.y + frame_space / 8 <= y && y <= rect.y + rect.h - frame_space / 8)
	{
		show = HIDDEN;
		for (auto& bullet : bullet_list)
		{
			delete bullet;
			bullet = nullptr;
		}
		bullet_list.clear();
		return true;
	}
	return false;
}
Boss::Boss()
{
	HP = maxHP = 0;
	shield = shield_time = 0;
	heal = heal_time = 0;
	maxHP_bar.x = maxHP_bar.y = maxHP_bar.w = maxHP_bar.h = 0;
	currentHP_bar.x = currentHP_bar.x = currentHP_bar.x = currentHP_bar.x = 0;
}
Boss::~Boss()
{

}
void Boss::setHPBar(const int& x, const int& y)
{
	maxHP_bar.x = currentHP_bar.x = x;
	maxHP_bar.y = currentHP_bar.y = y;

	currentHP_bar.w = maxHP_bar.w = 15 * TILE_SIZE;
	currentHP_bar.h = maxHP_bar.h = TILE_SIZE / 2;
}
void Boss::DrawHPBar(SDL_Renderer* scr)
{
	currentHP_bar.w = HP * maxHP_bar.w / maxHP;
	if (shield_time == 0)
		SDL_SetRenderDrawColor(scr, 207, 11, 11, 255);
	else SDL_SetRenderDrawColor(scr, 0, 238, 255, 255);
	SDL_RenderFillRect(scr, &currentHP_bar);
	SDL_SetRenderDrawColor(scr, 0, 0, 0, 255);
	SDL_RenderDrawRect(scr, &maxHP_bar);
	SDL_Rect renderquad = maxHP_bar;
	for (int i = 1; i < 5; ++i)
	{
		renderquad.x++;
		renderquad.y++;
		renderquad.w -= 2;
		renderquad.h -= 2;
		SDL_RenderDrawRect(scr, &renderquad);
	}
	SDL_SetRenderDrawColor(scr, 255, 255, 255, 255);
	int shield_width = maxHP_bar.w;
	for (int i = 1; i < 7; ++i)
	{
		shield_width = shield_time * maxHP_bar.w / shield;
		SDL_RenderDrawLine(scr, maxHP_bar.x, maxHP_bar.y + maxHP_bar.h + i,
								maxHP_bar.x + shield_width, maxHP_bar.y + maxHP_bar.h + i);
	}
}
bool Boss::checkBulletHit(const int& x, const int& y)
{
	return (Threads::checkBulletHit(x, y));
}
bool Boss::loadImg(std::string filepath, SDL_Renderer* scr, std::string filepath2)
{
	return Threads::loadImg(filepath, scr, filepath2);
}
void Boss::render(SDL_Renderer* scr)
{
	Threads::render(scr);
	DrawHPBar(scr);
}
void Boss::update(SDL_Rect mainChar_position, SDL_Renderer* scr)
{
	Threads::update(mainChar_position, scr);
	if (shield_time > 0)
		shield_time--;
}
void Boss::setRect(int x, int y)
{
	rect.x = x;
	rect.y = y;
	setHPBar(7 * TILE_SIZE, (int)(1.8 * TILE_SIZE));
}
void Boss::kill()
{
	if (HP > 0)
	{
		show = SHOW;
		if (shield_time == 0)
		{
			shield_time = shield;
			HP--;
		}
		else
		{
			HP++;
			if (HP > maxHP) HP = maxHP;
		}
	}
	if (HP == 0)
	{
		show = HIDDEN;
		maxHP_bar.x = maxHP_bar.y = maxHP_bar.w = maxHP_bar.h = 0;
		currentHP_bar.x = currentHP_bar.x = currentHP_bar.x = currentHP_bar.x = 0;
	}
}