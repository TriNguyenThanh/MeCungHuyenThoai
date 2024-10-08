#include "SetUp.h"

bool init() {
	bool success = true;
	// chuan bi moi truong tao cua so, render, am thanh
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		success = false;
	else
	{
		// khu rang cua
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		//tao cua so
		window = SDL_CreateWindow("ME CUNG HUYEN THOAI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HIGHT, SDL_WINDOW_SHOWN);

		if (window == nullptr)
			success = false;
		else
		{
			// khoi tao screen control de ve object
			screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

void close() {

	SDL_DestroyRenderer(screen); //giai phong screen control
	screen = NULL;

	SDL_DestroyWindow(window); //giai phong window control
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}
GameMap game_map;
MainObject player;


void start() {
	if (init() == false) return;				// khoi tao game
	bool ret = game_map.loadMap(screen);
	if (ret == false) return;

	player.loadImg("assets\\player\\sky\\run_right - Copy.png", screen);
	player.setClip();
	player.setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);

	Timer fpsControl;
	bool is_quit = false;
	int current_map_index = 0;
	game_map.setCurrentMap(current_map_index);

	SDL_Rect fog = { 0, 0, SCREEN_WIDTH, SCREEN_HIGHT };

	//BaseObject background, map;
	//background.loadImg("assets\\map\\map01\\bg01.png", screen);
	//map.loadImg("assets\\map\\map01\\map01.png", screen);

	while (!is_quit) {

		while (SDL_PollEvent(&event) != NULL) { // bat su kien nguoi dung
			if (event.type == SDL_QUIT)
				is_quit = true;
			player.getInput(event, screen);
		}
		SDL_SetRenderDrawColor(screen, Render_Draw_Color_red, Render_Draw_Color_green, Render_Draw_Color_blue, 255); // mau nen
		SDL_RenderClear(screen); // clear man hinh

		//SDL_SetTextureAlphaMod(game_map.getMap().background.getObject(), 128);
		game_map.DrawBackMap(screen); // ve background len man hinh
		//SDL_SetRenderDrawColor(screen, 255, 255, 255, 20);
		//SDL_RenderFillRect(screen, &fog);
		player.moveBullet(game_map, screen);
		player.movePlayer(game_map);
		
		player.show(screen);
		game_map.DrawFrontMap(screen);
		//background.render(screen, nullptr);
		//map.render(screen, nullptr);
		SDL_RenderPresent(screen); // update lai man hinh

		//gioi han fps
		int real_time = fpsControl.get_tick();
		int time_one_frame = 1000 / FPS;
		if (real_time < time_one_frame)
			SDL_Delay(time_one_frame - real_time);
	}
}