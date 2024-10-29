#pragma once

#include "function.h"
#include "ThreadBulletObject.h"

class Threads {
public:
	Threads();
	virtual ~Threads(); 
	 virtual bool loadImg(std::string filepath, SDL_Renderer * scr, std::string filepath2 = "none");
	 virtual void render(SDL_Renderer* scr);
	 virtual void update(SDL_Rect mainChar_position, SDL_Renderer* scr);
	 virtual void setRect(int x, int y);
	 void setClip();
	 void setFrame(int x) { frame_count = x; }
	 void setMove(bool move_) { move = move_; }
	 void setFire(bool fire_) { fire = fire_; }
	 void setFireDelay(int fire_delay_time_);
	 void setDes(int x, int y) { x_des = x; y_des = y; }
	 void setSpawn(int x, int y);
	 void setName(std::string name_) { name = name_; }
	 void setMoveDir(int dir_) { move_dir = dir_; }
	 void setTarget(std::string target_type) { target = target_type; }

	 bool isLive() const { return show == SHOW; }
	 bool is_attack() const { return fire; }
	 bool checkRectHit(int tile_map[MAX_MAP_Y][MAX_MAP_X], SDL_Rect rect_); // vien dan va cham voi map va thread va cham voi nguoi choi
	 virtual bool checkBulletHit(const int& x, const int& y); // va cham voi bullet cua nguoi choi

	 virtual void kill() { show = HIDDEN; }
	 void spawn() { show = SHOW; }
	 void attack(SDL_Renderer* scr);
	 // boss
	 virtual void setHPBar(const int& x, const int& y) {}
	 virtual void DrawHPBar(SDL_Renderer* scr) {}
	 virtual void setHP(const int& x) {}
	 virtual void setHeal(const int& x) {}
	 virtual void setShield(const int& x) {}
	 virtual int getHP() { return 0; }
protected:
	std::string name;

	int x_pos;
	int y_pos;

	int x_spawn;
	int y_spawn;

	int x_des;
	int y_des;

	int frame;            // so thu tu frame hien tai
	int frame_count;      // so frame tong cong trong sheets
	int frame_width;      
	int frame_hight;
	SDL_Rect clip[20];
	SDL_Texture* texture;
	SDL_Texture* idle_texture;
	SDL_Texture* attack_texture;
	SDL_Rect rect;

	bool fire;					// Quai co the bang hay khong
	int fire_delay;				// thoi gian delay tong cong 
	int fire_delay_time;		// thoi gian delay hien tai
	std::vector<ThreadBullet*> bullet_list;
	
	int x_target;
	int y_target;

	bool move;
	int move_dir; // huong di chuyen
	int dir;      // huong nhin

	std::string target;

	int show;
};

class Boss : public Threads
{
public:
	Boss();
	~Boss();
	bool loadImg(std::string filepath, SDL_Renderer* scr, std::string filepath2 = "none");
	void render(SDL_Renderer* scr);
	void setRect(int x, int y);
	void update(SDL_Rect mainChar_position, SDL_Renderer* scr);
	void setHPBar(const int& x, const int& y);
	void DrawHPBar(SDL_Renderer* scr);
	bool checkBulletHit(const int& x, const int& y);
	void kill();
	void setHP(const int& x) { HP = maxHP = x; }
	void setHeal(const int& x) { heal = heal_time = x; }
	void setShield(const int& x) { shield_time = 0; shield = x; }
	int getHP() const { return HP; }
private:
	int maxHP; // mau toi da
	int HP;     // mau hien tai

	int shield; // thoi gian cua khien ton tai
	int shield_time; // thoi gian hien tai

	int heal;  // thoi gian heal toi da
	int heal_time; // thoi gian heal hien tai

	SDL_Rect maxHP_bar;
	SDL_Rect currentHP_bar;
};
// ve thanh HP