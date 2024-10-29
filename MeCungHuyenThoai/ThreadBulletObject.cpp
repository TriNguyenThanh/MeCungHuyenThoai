#include "ThreadBulletObject.h"

ThreadBullet::ThreadBullet()
{
	name = "none";
	rect.x = rect.y = rect.w = rect.h = 0;
	texture = nullptr;
	
	x_pos = y_pos = x_des = y_des = 0;
	x_val = y_val = 0.0;
	
	is_move = false;

	dir = STAND;
	angle = 0;
}
ThreadBullet::~ThreadBullet()
{

}
bool ThreadBullet::loadImg(std::string filepath, SDL_Renderer* scr)
{
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	SDL_SetColorKey(surface, SDL_TRUE, BACKGROUND_COLOR);
	if (!surface) return false;

	rect.w = surface->w;
	rect.h = surface->h;

	texture = SDL_CreateTextureFromSurface(scr, surface);

	SDL_FreeSurface(surface);

	return true;
}
void ThreadBullet::setRect(const int& x, const int& y)
{
	x_pos = rect.x = x;
	y_pos = rect.y = y;
}
void ThreadBullet::setMove(bool move_)
{
	is_move = move_;
}
void ThreadBullet::setDes(const int& x, const int& y)
{
	x_des = x;
	y_des = y;
	
	/*float thread_bullet_speed = MAGMA_BALL_SPEED;*/
	float thread_bullet_speed = 0.0;
	std::string magma_ball = "magma_ball";
	std::string dragon_fire = "dragon_fire";
	if (name == magma_ball) thread_bullet_speed = MAGMA_BALL_SPEED;
	else if (name == dragon_fire) thread_bullet_speed = DRAGON_FIRE_SPEED;

	if (x_des == x_pos)
	{
		if (y_des > y_pos)
		{
			angle = 0;
			dir = DOWN;
			x_val = 0;
			y_val = thread_bullet_speed;
		}	
		else
		{
			angle = 180;
			dir = UP;
			x_val = 0;
			y_val = -thread_bullet_speed;
		}
	}
	else if (y_des == y_pos)
	{
		if (x_des > x_pos)
		{
			angle = -90;
			dir = RIGHT;
			x_val = thread_bullet_speed;
			y_val = 0;

		}
		else
		{
			angle = 90;
			dir = LEFT;
			x_val = -thread_bullet_speed;
			y_val = 0;
		} 
	}
	else
	{
		dir = STAND;
		double a = atan((double)(y_des - y_pos) / (double)(x_des - x_pos));
		angle = (float)(a * 180.0 / M_PI) - 90;
		x_val = (float)( (float) thread_bullet_speed * cos(a));
		y_val = (float)( (float) thread_bullet_speed * sin(a));   

		if (x_des < x_pos)
		{
			x_val = -x_val;
			y_val = -y_val;
			angle += 180.0;
		}
	}
}
void ThreadBullet::render(SDL_Renderer* scr)
{
	SDL_RenderCopyEx(scr, texture, nullptr, &rect, angle, 0, SDL_FLIP_NONE);
	rect.x = x_pos;
	rect.y = y_pos;
}
void ThreadBullet::move_bullet()
{
	if (is_move)
	{
		x_pos += (int) roundf(x_val);
		y_pos += (int) roundf(y_val);

		if (x_pos < 0 || x_pos > SCREEN_WIDTH || y_pos < 0 || y_pos > SCREEN_HIGHT)
			is_move = false;
	}
}
bool ThreadBullet::checkHit(int tile_map[MAX_MAP_Y][MAX_MAP_X], SDL_Rect rect_)
{
	int dem = 0;
	if (rect_.x + FRAME_SPACE + 10 + rect_.w < this->rect.x || this->rect.x + this->rect.w < rect_.x + FRAME_SPACE + 10) dem++;
	if (rect_.y - 35 + rect_.h < this->rect.y || this->rect.y + this->rect.h < rect_.y + 35) dem++;

	int x = (this->rect.x + this->rect.w / 2) / TILE_SIZE;
	int y = (this->rect.y + this->rect.h / 2) / TILE_SIZE;

	if (tile_map[y][x] != 0 && tile_map[y][x] != 2 && tile_map[y][x] != 5 && tile_map[y][x] != 6) {
		is_move = 0;
		return false;
	}

	if (!dem)
	{
		is_move = false;
		return true;
	}
	return false;
}