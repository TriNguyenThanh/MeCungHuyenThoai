#include "ItemObject.h"

Item::Item()
{
	status = SHOW;
	name = "none";
}
Item::~Item()
{
	;
}
void Item::render(SDL_Renderer* scr)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, TILE_SIZE, TILE_SIZE };
	SDL_SetTextureAlphaMod(object_, status);
	SDL_RenderCopy(scr, object_, nullptr, &renderquad);
}