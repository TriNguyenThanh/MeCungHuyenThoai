#include "BulletObject.h"

Bullet::Bullet()
{
	x_val = 0;
	y_val = 0;

	is_move = 0;
	dir = RIGHT;
}
Bullet::~Bullet() {

}
void Bullet::render(SDL_Renderer* scr)
{
	double angle = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	if (dir == LEFT)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else if (dir == UP)
	{
		angle = -90;
	}
	SDL_RenderCopyEx(scr, object_, nullptr, &rect_, angle, 0, flip);
}
void Bullet::move(GameMap& game_map)
{
	if (dir == UP)
	{
		rect_.y -= y_val;
		if (rect_.y < 0)
		{
			is_move = 0;
		}
	}
	else if (dir == LEFT)
	{
		rect_.x -= x_val;
		if (rect_.x < 0)
		{
			is_move = 0;
		}
	}
	else if (dir == RIGHT)
	{
		rect_.x += x_val;
		if (rect_.x > (SCREEN_WIDTH - 150))
		{
			is_move = 0;
		}
	}
	
	checkHit(game_map);
}
void Bullet::checkHit(GameMap& game_map) // dan ban vao quai
{
	MapObject mapData = game_map.getMap();

	for (auto& i : mapData.threads_list)
	{
		if (i->isLive())
		{
			if (i->checkBulletHit(rect_.x + rect_.w / 2, rect_.y + rect_.h / 2))
			{
				i->kill();
				is_move = 0;
				return;
			}
		}
	}
	int x = (rect_.x + rect_.w / 2) / TILE_SIZE;
	int y = (rect_.y + rect_.h/ 2) / TILE_SIZE;

	if (mapData.tile[y][x] != 0 && mapData.tile[y][x] != 2 && mapData.tile[y][x] != 5 && mapData.tile[y][x] != 6) {
		is_move = 0;
		return;
	}
}