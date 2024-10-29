#pragma once
#include "function.h"

class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();
	bool LoadSound(std::string climb_path, std::string crystal_pick_up_path, std::string mana_pick_up_path, std::string jump_path, std::string land_path, std::string fire_path, std::string death_path, std::string walk_path, std::string background_path, std::string boss_fight_path, std::string victory_path);
	void free();
	void playChunk(Mix_Chunk* tmp) const { Mix_PlayChannel(-1, tmp, 0); }
	void playBackground() const { Mix_PlayMusic(background, -1); }
	void playBossFight() const { Mix_PlayMusic(bossFight, -1); }
	void playVictory() const { Mix_PlayMusic(victory, -1); }
	void playJump() const { Mix_PlayChannel(-1, jump, 0); }
	void playCrystalPickUp() const { Mix_PlayChannel(-1, crystal_pick_up, 0); }
	void playManaPickUp() const { Mix_PlayChannel(-1, mana_pick_up, 0); }
	void playLand() const { Mix_PlayChannel(-1, land, 0); }
	void playFire() const { Mix_PlayChannel(-1, fire, 0); }
	void playDeath() const { Mix_PlayChannel(-1, death, 0); }
	void playWalk() const { Mix_PlayChannel(-1, walk, 0); }
	void playClimb() const { Mix_PlayChannel(15, climb, 0); }

private:
	Mix_Chunk* climb;
	Mix_Chunk* crystal_pick_up;
	Mix_Chunk* mana_pick_up;
	Mix_Chunk* jump;
	Mix_Chunk* land;
	Mix_Chunk* fire;
	Mix_Chunk* death;
	Mix_Chunk* walk;

	Mix_Music* background;
	Mix_Music* bossFight;
	Mix_Music* victory;
};