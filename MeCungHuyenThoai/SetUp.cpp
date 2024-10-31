#include "SetUp.h"

bool init() {
	SetProcessDPIAware(); // nhan biet DPI cua man hinh


	bool success = true;
	// chuan bi moi truong tao cua so, render, am thanh
	bool ret = (SDL_Init(SDL_INIT_VIDEO) >= 0);
	ret = (	TTF_Init() != -1 && // khoi tao thu vien TTF
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) != -1 && // khoi tao thu vien am thanh
			Mix_AllocateChannels(16) != -1); // dat so luong kenh am thanh
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

		SDL_Surface* icon = IMG_Load("assets\\icon\\icon.png");
		SDL_SetWindowIcon(window, icon);

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
// cac bien quan ly tro choi
GameMap game_map;
MainObject player;
StatusBar status_bar;
SoundEffect sound_effect;
Menu start_menu;
Menu tutorial_menu;
Menu win_menu;
Menu lose_menu;

// flags
bool ADMIN = true;
bool is_quit = false;
bool is_start = false;
bool is_restart = false;
bool is_unpause = false;
bool is_win = false;
bool is_lose = false;

bool loadData() {
	bool ret = game_map.loadMap(screen);
	if (ret == false) return false;
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
		"assets\\screen\\statusbar\\shield.png",
		"assets\\screen\\statusbar\\mana.png",
		"assets\\screen\\statusbar\\minimap.png",
		"assets\\screen\\statusbar\\restart_button.png",
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
		"assets\\sound\\music\\BossFight.mp3",
		"assets\\sound\\music\\victory.mp3",
		"assets\\sound\\music\\defeat.mp3");
	if (!ret) return false;
	
	start_menu.setText("THE LEGENDARY MAZE", "START", "QUIT");
	start_menu.setFontSize(120, 70);
	start_menu.setRect(420, 270, 655, 692, 1130, 692);
	ret = start_menu.loadImg(
		"assets\\screen\\Menu\\MainMenu.png",
		"assets\\screen\\Menu\\MainMenuBG.png",
		"assets\\screen\\Menu\\MainMenuBG_run.png",
		SpeedRushItalic, screen);
	if (!ret) return false;

	tutorial_menu.setText("", "Done", "none");
	tutorial_menu.setFontSize(120, 70);
	tutorial_menu.setRect(0, 0, 1370, 887, 0, 0);
	ret = tutorial_menu.loadImg(
		"assets\\screen\\Menu\\Tutorial.png",
		"assets\\screen\\Menu\\MainMenuBG.png",
		"none", SpeedRushItalic, screen);
	if (!ret) return false;

	win_menu.setText("YOU ARE THE WINNER", "restart", "none");
	win_menu.setFontSize(90, 50);
	win_menu.setRect(600, 220, 880, 520, 0, 0);
	ret = win_menu.loadImg(
		"assets\\screen\\Menu\\SubMenu.png",
		"assets\\screen\\Menu\\SubMenuBG.png",
		"none", SpeedRushItalic, screen);
	if (!ret) return false;

	lose_menu.setText("LOSER! AHAHAHAHA", "restart", "none");
	lose_menu.setFontSize(90, 50);
	lose_menu.setRect(610, 220, 880, 520, 0, 0);
	ret = lose_menu.loadImg(
		"assets\\screen\\Menu\\SubMenu.png",
		"assets\\screen\\Menu\\SubMenuBG.png",
		"none", SpeedRushItalic, screen);
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
void restart()
{
	if (is_restart)
	{
		game_map.clear();

		bool ret = game_map.loadMap(screen);
		if (!ret) return;

		int current_map_index = 1;
		game_map.setCurrentMap(current_map_index);
		player.setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
		player.reset();
	}
	is_start = false;
	is_quit = false;
	is_restart = false;
	is_unpause = false;
	is_win = false;
	is_lose = false;

	Mix_HaltMusic();
	sound_effect.playBackground();
}

void start() {
	if (init() == false) return;				// khoi tao game
	if (loadData() == false) return;            // load map

	Timer fpsControl;
	
	sound_effect.playBackground();

	fpsControl.start_count();
	while (!is_quit) {
		fpsControl.begin();

		while (SDL_PollEvent(&event) != NULL) { // bat su kien nguoi dung
			if (event.type == SDL_QUIT)
				is_quit = true;

			// lien ket nut bam voi vong lap
			if (is_lose || is_win)
			{
				if (is_win)
					win_menu.click(screen, event, is_restart, is_quit);
				else lose_menu.click(screen, event, is_restart, is_quit);
			}
			else if (!is_start)
			{
				if (!is_unpause)
				{
					start_menu.click(screen, event, is_unpause, is_quit);
				}
				else
				{
					tutorial_menu.click(screen, event, is_start, is_quit);
				}
			}
			else
			{
				player.getInput(event, screen, sound_effect);
				status_bar.getInput(screen, event, is_quit, is_lose);
				if (!is_unpause)
				{
					start_menu.click(screen, event, is_unpause, is_quit);
				}

				if (event.type == SDL_KEYDOWN)
				{
					if (ADMIN)
					{
						switch (event.key.keysym.sym)
						{
						case SDLK_0:
							game_map.setCurrentMap(0);
							break;
						case SDLK_1:
							game_map.setCurrentMap(1);
							break;
						case SDLK_2:
							game_map.setCurrentMap(2);
							break;
						case SDLK_3:
							game_map.setCurrentMap(3);
							break;
						case SDLK_4:
							game_map.setCurrentMap(4);
							break;
						case SDLK_5:
							game_map.setCurrentMap(5);
							break;
						case SDLK_r:
							is_restart = true;
							break;
						case SDLK_t:
							player.setToLose();
							break;
						case SDLK_y:
							player.setToWin();
							break;
						}
						if (event.key.keysym.sym >= 48 && event.key.keysym.sym <= 53)
							player.setSpawn(game_map.getMap().spawn_x * TILE_SIZE, game_map.getMap().spawn_y * TILE_SIZE);
					}
				}
				if (event.type == SDL_KEYUP)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						is_unpause = (is_unpause == false);
						break;
					case SDLK_F1:
						is_start = false;
					}
				}
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				if (is_win)
				{
					win_menu.hover(screen);
				}
				else if (is_lose)
				{
					lose_menu.hover(screen);
				}
				else if (!is_start && is_unpause)
				{
					tutorial_menu.hover(screen);
				}
				else if (!is_unpause)
				{
					start_menu.hover(screen);
				}
					
			}
		}
		if (is_restart) restart();
		if (is_win || is_lose)
		{
			is_unpause = false;
			is_start = false;
			if (is_win)
			{
				win_menu.render(screen);
			}
			else
			{
				lose_menu.render(screen);
			}
		}
		else if (is_unpause && is_start)
		{
			SDL_SetRenderDrawColor(screen, Render_Draw_Color_red, Render_Draw_Color_green, Render_Draw_Color_blue, SHOW); // mau nen
			SDL_RenderClear(screen); // clear man hinh

			game_map.DrawBackMap(screen); // ve background len man hinh
			game_map.DrawHiddenObject(screen);
			game_map.update(player.getRect(), screen);

			player.moveBullet(game_map, screen);
			player.movePlayer(game_map, sound_effect);
			player.show(screen, sound_effect);
			game_map.DrawFrontMap(screen);
			status_bar.update(screen, player, game_map, is_win, is_lose);
			status_bar.render(screen);

			if (is_win)
			{
				Mix_HaltMusic();
				sound_effect.playVictory();
			}
			if (is_lose)
			{
				Mix_HaltMusic();
				sound_effect.playDefeat();
			}
		}
		else if (is_unpause)
		{
			tutorial_menu.render(screen);
		}
		else
		{
			start_menu.update();
			start_menu.render(screen);
		}

		fpsControl.drawFPS(screen);
		SDL_RenderPresent(screen); // update lai man hinh

		//gioi han fps
		fpsControl.end();
		fpsControl.lockFPS(FPS);
	}
}