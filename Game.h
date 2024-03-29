#pragma once

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )
#include "SDL2_ttf/include/SDL_ttf.h"
#pragma comment(lib, "SDL2_ttf/lib/x86/SDL2_ttf.lib")
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

#include "TextureManager.h"
#include "Player.h"
#include "Background.h"
#include "Entity.h"
#include "Text.h"
#include"Collision.h"
#include"Object.h"
#include "Audio.h"

#define WINDOW_WIDTH	1680
#define WINDOW_HEIGHT	1050
#define MAX_KEYS		256
#define MAX_SHOTS		32

class Game
{
public:
	Game();
	~Game();

	bool Init();
	bool LoadImages();
	void Release();
	
	bool Input();
	bool Update();
	void Draw();
	void Text(const char* msg, int x, int y, int r, int g, int b);

	void Event();

	void playMusicMenu();
	void playMusicGame();
	void playMusicEnd();

	void OpenIntro();
	void OpenMenu();
	void OpenEnd();
	bool timerReady = false;
	bool intro = false;
	bool close = false;
	bool end = true;
	bool gameReady = true; 
	bool play = true;
	bool player = true;
	int points = 0;
	int time1 = 0, time2 = 0, time3 = 0;
	static bool CheckCollision(SDL_Rect* A, SDL_Rect* B);

	int posYD1 = 0;
	int posYD2 = 0;
	int posYD3 = 0;
	bool dead = false;

	int wave = 0;
	int endwave = 0;

	bool e1 = true;
	int e1prob = 0;
	bool e2 = true;
	int e2prob = 0;
	bool e3 = true;
	int e3prob = 0;

	int egg1count = 0;
	int egg2count = 0;
	int egg3count = 0;

	bool num01 = false;
	bool num02 = false;
	bool num03 = true;

	unsigned int buttonFX;
	unsigned int eggFX;

	void timer();

private:
	SDL_Window *Window;
	SDL_Renderer *Renderer;
	SDL_Texture *img_background, *img_shot, *background, *in, *menu, *endmenu, *tex, *towd, *towu, *egg1, *egg2, *egg3, *num1, * num2, * num3, * egg1c, * egg2c, * egg3c, *clouds, * egg1cend, * egg2cend, * egg3cend;
	
	int idx_shot;

	bool god_mode;

	enum KEY_STATE { KEY_IDLE, KEY_DOWN, KEY_REPEAT, KEY_UP	};
	KEY_STATE keys[MAX_KEYS]; 

	Player p, shot;
	bool GameState;

	Entity Player, Shots[MAX_SHOTS], Scene, Menu, EndMenu, TowD1, TowD2, TowD3, TowU1, TowU2, TowU3, Intro, Egg1, Egg2, Egg3, Num1, Num2, Num3, Eggc1, Eggc2, Eggc3, Clouds, Eggc1end, Eggc2end, Eggc3end;

	Audio audio;

	TTF_Font* font;
	/*Text score;*/

};
