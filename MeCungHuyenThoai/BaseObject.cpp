#include "BaseObject.h"

BaseObject::BaseObject() {
	object_ = NULL;
	rect_.x = rect_.y = rect_.w = rect_.h = 0;
}

BaseObject::~BaseObject() {

}

void BaseObject::setRect(int x, int y) {
	rect_.x = x;
	rect_.y = y;
}

SDL_Rect BaseObject::getRect() {
	return rect_;
}

SDL_Texture* BaseObject::getObject() {
	return object_;
}
//load file anh len object
bool BaseObject::loadImg(std::string filepath, SDL_Renderer* screen) {
	SDL_Texture* new_texture = NULL;			//tao moi texture			
	SDL_Surface* surface = IMG_Load(filepath.c_str());     	// load file hinh len texture

	if (surface != NULL) {
		SDL_SetColorKey(surface, SDL_TRUE, BACKGROUND_COLOR); 		// Xoa nen file anh
		new_texture = SDL_CreateTextureFromSurface(screen, surface); 		// chuyen doi surface sang texture
		if (new_texture != NULL) { 		// lay thong so cho khung hinh
			rect_.w = surface->w;
			rect_.h = surface->h;
		}
		SDL_FreeSurface(surface); 		// giai phong vung nho
	}
	SDL_DestroyTexture(object_);	// xoa vung nho cua texture hien tai
	object_ = new_texture;

	return object_ != NULL;
}

// Dua texture len screen control
void BaseObject::render(SDL_Renderer* des, const SDL_Rect* clip, SDL_RendererFlip flip) {
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h};
	SDL_RenderCopyEx(des, object_, clip, &renderquad,0, nullptr, flip);
}

//giai phong doi tuong 
void BaseObject::free() {
	if (object_ != NULL) {
		SDL_DestroyTexture(object_);
		object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}