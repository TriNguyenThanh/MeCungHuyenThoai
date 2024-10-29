#include "Sound.h"

SoundEffect::SoundEffect()
{
	climb = nullptr;
	crystal_pick_up = nullptr;
	mana_pick_up = nullptr;
	jump = nullptr;
	land = nullptr;
	fire = nullptr;
	death = nullptr;
	walk = nullptr;

	background = nullptr;
	bossFight = nullptr;
	victory = nullptr;
}
SoundEffect::~SoundEffect()
{
	;
}
bool SoundEffect::LoadSound(std::string climb_path,
							std::string crystal_pick_up_path,
							std::string mana_pick_up_path,
							std::string jump_path,
							std::string land_path,
							std::string fire_path,
							std::string death_path,
							std::string walk_path,
							std::string background_path,
							std::string boss_fight_path,
							std::string victory_path)
{
	climb = Mix_LoadWAV(climb_path.c_str());
	if (!climb) return false;
	crystal_pick_up = Mix_LoadWAV(crystal_pick_up_path.c_str());
	if (!crystal_pick_up) return false;
	Mix_VolumeChunk(crystal_pick_up, 90);

	death = Mix_LoadWAV(death_path.c_str());
	if (!death) return false;
	Mix_VolumeChunk(death, 128);
	fire = Mix_LoadWAV(fire_path.c_str());
	if (!fire) return false;
	Mix_VolumeChunk(fire, 128);

	jump = Mix_LoadWAV(jump_path.c_str());
	if (!jump) return false;
	Mix_VolumeChunk(jump, 128);

	land = Mix_LoadWAV(land_path.c_str());
	if (!land) return false;
	Mix_VolumeChunk(land, 128);
	mana_pick_up = Mix_LoadWAV(mana_pick_up_path.c_str());
	if (!mana_pick_up) return false;
	Mix_VolumeChunk(mana_pick_up, 128);
	walk = Mix_LoadWAV(walk_path.c_str());
	if (!walk) return false;
	Mix_VolumeChunk(walk, 80);

	background = Mix_LoadMUS(background_path.c_str());
	if (!background) return false;
	Mix_VolumeMusic(90);

	bossFight = Mix_LoadMUS(boss_fight_path.c_str());
	if (!bossFight) return false;
	Mix_VolumeMusic(90);

	victory = Mix_LoadMUS(victory_path.c_str());
	if (!victory) return false;

	return true;
}
void SoundEffect::free()
{
	Mix_FreeChunk(jump);
	Mix_FreeChunk(climb);
	Mix_FreeChunk(walk);
	Mix_FreeChunk(crystal_pick_up);
	Mix_FreeChunk(mana_pick_up);
	Mix_FreeChunk(land);
	Mix_FreeChunk(death);
	Mix_FreeChunk(fire);

	Mix_FreeMusic(background);
	Mix_FreeMusic(bossFight);
	Mix_FreeMusic(victory);
}