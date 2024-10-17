#include "SetUp.h"

bool init() {
	SetProcessDPIAware(); // nhan biet DPI cua man hinh
	bool success = true;
	// chuan bi moi truong tao cua so, render, am thanh
	bool ret = (SDL_Init(SDL_INIT_VIDEO) >= 0);
	ret = (	TTF_Init() != -1 &&
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) != -1 &&
			Mix_AllocateChannels(16) != -1);
	if (!ret)
		success = false;
	else
	{
		// khu rang cua
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		// Lay do phan giai cua man hinh hien tai
		SDL_Rect display;
		SDL_GetDisplayBounds(0, &display);

		if (display.w > SCREEN_WIDTH)
		{
			display.w = SCREEN_WIDTH;
			display.h = SCREEN_HIGHT;
		}

		//tao cua so
		window = SDL_CreateWindow("ME CUNG HUYEN THOAI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  display.w, display.h, SDL_WINDOW_SHOWN);

		if (window == nullptr)
			success = false;
		else
		{
			// khoi tao screen control de ve object
			screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			// dat ti le man hinh cho cua so game
			SDL_RenderSetLogicalSize(screen, SCREEN_WIDTH, SCREEN_HIGHT);

			SDL_SetRenderDrawBlendMode(screen, SDL_BLENDMODE_BLEND);
			if (screen == NULL)
				success = false;
			else
			{

				SDL_SetRenderDrawColor(screen, 180, 180, 180, 180);
				int imgFlag = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlag) && imgFlag))
					success = false;
			}
		}
	}

	return success;
}
GameMap game_map;
MainObject player;
StatusBar status_bar;
SoundEffect sound_effect;

bool loadData() {
	bool ret = game_map.loadMap(screen);
	if (!ret) return false;

	int current_map_index = 1;
	game_map.setCurrentMap(current_map_index);

	ret = player.loadAction(
		screen,
		"assets\\player\\BlueWizard\\idle.png",
		"assets\\player\\BlueWizard\\run.png",
		"assets\\player\\BlueWizard\\jump.png");
	if (!ret) return false;
	ret = player.loadImg("assets\\player\\BlueWizard\\idle.png", screen);
	if (!ret) return false;
	player.setClip();
	player.setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);

	ret = status_bar.loadimg(
		screen,
		"assets\\screen\\statusbar\\background.png",
		"assets\\screen\\statusbar\\life.png",
		"assets\\screen\\statusbar\\mana.png",
		"assets\\screen\\statusbar\\minimap.png",
		"assets\\screen\\statusbar\\quit_button.png");
	if (!ret) return false;
	// load am thanh
	ret = sound_effect.LoadSound(
		"assets\\sound\\effect\\climb.wav",
		"assets\\sound\\effect\\crystal_pick_up.wav",
		"assets\\sound\\effect\\mana_bottle_pick_up.wav",
		"assets\\sound\\effect\\jump.wav",
		"assets\\sound\\effect\\land.wav",
		"assets\\sound\\effect\\fire.wav",
		"assets\\sound\\effect\\death.wav",
		"assets\\sound\\effect\\step_on_grass.wav",
		"assets\\sound\\music\\background.mp3",
		"assets\\sound\\music\\victory.mp3");
	if (!ret) return false;
	return true;
}
void close() {

	SDL_DestroyRenderer(screen); //giai phong screen control
	screen = NULL;

	SDL_DestroyWindow(window); //giai phong window control
	window = NULL;

	sound_effect.free();
	Mix_CloseAudio();
	IMG_Quit();
	SDL_Quit();
}
void start() {
	if (init() == false) return;				// khoi tao game
	if (loadData() == false) return;

	Timer fpsControl;
	
	sound_effect.playBackground();
	bool is_quit = false;

	while (!is_quit) {
		
		while (SDL_PollEvent(&event) != NULL) { // bat su kien nguoi dung
			if (event.type == SDL_QUIT)
				is_quit = true;
			player.getInput(event, screen, sound_effect);
			status_bar.getInput(screen, event, is_quit);
		}
		SDL_SetRenderDrawColor(screen, Render_Draw_Color_red, Render_Draw_Color_green, Render_Draw_Color_blue, SHOW); // mau nen
		SDL_RenderClear(screen); // clear man hinh

		game_map.UpdateHiddenObject();
		game_map.DrawBackMap(screen); // ve background len man hinh
		game_map.DrawHiddenObject(screen);

		player.moveBullet(game_map, screen);
		player.movePlayer(game_map, sound_effect);
		player.show(screen, sound_effect);

		status_bar.update(screen, player, game_map);
		
		game_map.DrawFrontMap(screen);
		status_bar.render(screen);

		SDL_RenderPresent(screen); // update lai man hinh

		//gioi han fps
		int real_time = fpsControl.get_tick();
		int time_one_frame = 1000 / FPS;
		if (real_time < time_one_frame)
			SDL_Delay(time_one_frame - real_time);
	}
}