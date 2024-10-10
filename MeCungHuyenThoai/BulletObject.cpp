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
void Bullet::move(GameMap& game_map)
{
	if (dir == LEFT)
	{
		rect_.x -= x_val;
		if (rect_.x < 0)
		{
			is_move = 0;
		}
	}
	else
	{
		rect_.x += x_val;
		if (rect_.x > (SCREEN_WIDTH - 150))
		{
			is_move = 0;
		}
	}
	checkHit(game_map);
}
void Bullet::checkHit(GameMap& game_map)
{
	MapObject mapData = game_map.getMap();
	int x = (rect_.x + 20) / TILE_SIZE;
	int y = (rect_.y + 10) / TILE_SIZE;

	if (mapData.tile[y][x] != 0) {
		is_move = 0;
	}
}