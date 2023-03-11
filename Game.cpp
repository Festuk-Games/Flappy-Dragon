#include "Game.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#define OGG_MUSIC

using namespace std;
Mix_Music* gMusic = NULL;

Game::Game() {
	Window = NULL;
	Renderer = NULL;
	GameState = false;
	TTF_Init();
	//sprite dimension
	p.setSource(0,0,60*3,46*3);
	//Pipe.setSource(0, 0, 217, 218);
	//destination dimension
	p.setDest(100, 200, 60*3, 46*3);
	//Pipe.setDest(100, 200, 400, 400);
	srand(time(NULL));

}
Game::~Game(){}

bool Game::Init()
{
	//Initialize SDL with all subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//Create our window: title, x, y, w, h, flags
	Window = SDL_CreateWindow("Flappy Dragon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == NULL)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}
	//Create a 2D rendering context for a window: window, device index, flags
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == NULL)
	{
		SDL_Log("Unable to create rendering context: %s", SDL_GetError());
		return false;
	}
	else
	{
		GameState = true;
	/*	Pipe.CreateTexture("spaceship.png", Renderer);*/
		p.CreateTexture("dragon1.png", Renderer);
		p.CreateTexture1("dragon2.png", Renderer);
		p.CreateTexture2("dragon3.png", Renderer);
		p.CreateTexture3("dragon4.png", Renderer);
		shot.CreateTexture("shot.png", Renderer);
	}

	//initialize music
	audio.Init();
	//play music

	//Initialize keys array
	for (int i = 0; i < MAX_KEYS; ++i)
		keys[i] = KEY_IDLE;

	//Load images
	if (!LoadImages())
		return false;

	//Init variables
	//size: 104x82
	/*Player.Init(20, WINDOW_HEIGHT >> 1, 104, 82, 5);*/
	idx_shot = 0;
	int w;
	SDL_QueryTexture(pause, NULL, NULL, &w, NULL);
	Pause.Init(0, 0, 400, 400, 4);
	SDL_QueryTexture(in, NULL, NULL, &w, NULL);
	Intro.Init(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 4);
	SDL_QueryTexture(menu, NULL, NULL, &w, NULL);
	Menu.Init(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 4);
	SDL_QueryTexture(endmenu, NULL, NULL, &w, NULL);
	EndMenu.Init(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 4);
	SDL_QueryTexture(img_background, NULL, NULL, &w, NULL);
	Scene.Init(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 4);
	SDL_QueryTexture(towd, NULL, NULL, &w, NULL);
	TowD1.Init(1920, 700, 59 *3, 180*3, 4);
	TowD2.Init(2600, 700, 59 * 3, 180 * 3, 4);
	TowD3.Init(3350, 750, 59 * 3, 180 * 3, 4);
	SDL_QueryTexture(towu, NULL, NULL, &w, NULL);
	TowU1.Init(1920, -300, 59 * 3, 180 * 3, 4);
	TowU2.Init(2600, -300, 59 * 3, 180 * 3, 4);
	TowU3.Init(3350, -250, 59 * 3, 180 * 3, 4);
	font = TTF_OpenFont("Fonts/PIXELADE.ttf", 50);

	SDL_QueryTexture(egg1, NULL, NULL, &w, NULL);
	Egg1.Init(1000, 400, 50, 50, 4);
	SDL_QueryTexture(egg2, NULL, NULL, &w, NULL);
	Egg2.Init(1640, 400, 50, 50, 4);
	SDL_QueryTexture(egg3, NULL, NULL, &w, NULL);
	Egg3.Init(2280, 400, 50, 50, 4);

	SDL_QueryTexture(egg1c, NULL, NULL, &w, NULL);
	Eggc1.Init(40, 105, 40, 40, 4);
	SDL_QueryTexture(egg2c, NULL, NULL, &w, NULL);
	Eggc2.Init(40, 155, 40, 40, 4);
	SDL_QueryTexture(egg3c, NULL, NULL, &w, NULL);
	Eggc3.Init(40, 205, 40, 40, 4);

	god_mode = false;
	return true;
}


bool Game::LoadImages()
{
	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_Log("IMG_Init, failed to init required png support: %s\n", IMG_GetError());
		return false;
	}
	menu = SDL_CreateTextureFromSurface(Renderer, IMG_Load("menu.png"));
	if (menu == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	in = SDL_CreateTextureFromSurface(Renderer, IMG_Load("logo.png"));
	if (in == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	endmenu = SDL_CreateTextureFromSurface(Renderer, IMG_Load("end.png"));
	if (endmenu == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	img_background = SDL_CreateTextureFromSurface(Renderer, IMG_Load("fondo.png"));
	if (img_background == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	towd = SDL_CreateTextureFromSurface(Renderer, IMG_Load("towerd.png"));
	if (towd == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	towu = SDL_CreateTextureFromSurface(Renderer, IMG_Load("toweru.png"));
	if (towu == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	//img_shot = SDL_CreateTextureFromSurface(Renderer, IMG_Load("shot.png"));
	//if (img_shot == NULL) {
	//	SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
	//	return false;
	//}
	egg1 = SDL_CreateTextureFromSurface(Renderer, IMG_Load("coin.png"));
	if (egg1 == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	egg2 = SDL_CreateTextureFromSurface(Renderer, IMG_Load("coin.png"));
	if (egg2 == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	egg3 = SDL_CreateTextureFromSurface(Renderer, IMG_Load("coin.png"));
	if (egg3 == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	egg1c = SDL_CreateTextureFromSurface(Renderer, IMG_Load("coin.png"));
	if (egg1c == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	egg2c = SDL_CreateTextureFromSurface(Renderer, IMG_Load("coin.png"));
	if (egg2c == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	egg3c = SDL_CreateTextureFromSurface(Renderer, IMG_Load("coin.png"));
	if (egg3c == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	pause = SDL_CreateTextureFromSurface(Renderer, IMG_Load("coin.png"));
	if (pause == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}

	return true;
}
void Game::Release()
{
	//Release images
	SDL_DestroyTexture(img_background);
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(endmenu);
	SDL_DestroyTexture(in);
	SDL_DestroyTexture(img_shot);
	SDL_DestroyTexture(towd);
	SDL_DestroyTexture(towu);
	SDL_DestroyTexture(egg1);
	SDL_DestroyTexture(egg2);
	SDL_DestroyTexture(egg3);
	SDL_DestroyTexture(egg1c);
	SDL_DestroyTexture(egg2c);
	SDL_DestroyTexture(egg3c);
	SDL_DestroyTexture(pause);

	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	//Clean up all SDL initialized subsystems
	SDL_Quit();
}

bool Game::Input()
{
	p.GetJumpTime();
	SDL_Event event;
	SDL_PollEvent(&event);
		
	if (event.type == SDL_QUIT)
	{
		GameState = false;
		Release();
		return false;
	}
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			if (!dead)
			{
				if (!p.JumpState())
				{
					p.Jump();
				}
				else
				{
					p.Gravity();
				}
			}
			else
			{
				p.Gravity();
			}
		}
	}
	else
	{
		
	}		


	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}

	return true;
}
bool Game::Update()
{
	//Read Input
	if (!Input())	return true;
	//Process Input
	int fx = 0, fy = 0;
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)	close = true;
	if (keys[SDL_SCANCODE_F1] == KEY_DOWN)		god_mode = !god_mode;
	if (keys[SDL_SCANCODE_UP] == KEY_REPEAT)	fy = -1;
	if (keys[SDL_SCANCODE_DOWN] == KEY_REPEAT)	fy = 1;
	if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT)	fx = -1;
	if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT)	fx = 1;
	//if (keys[SDLK_LCTRL] == KEY_DOWN)
	//{
	//	points += 1;
	//	//get player ypos
	//	int Ypos = p.Ypo();
	//	//size: 56x20
	//	//offset from player: dx, dy = [(29, 3), (29, 59)]
	//	Shots[idx_shot].Init(360, Ypos+100, 56, 20, 10);
	//	idx_shot++;
	//	idx_shot %= MAX_SHOTS;
	//}

	return false;
}



void Game::OpenIntro()
{
	SDL_Rect rc;
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
	//Clear rendering target
	SDL_RenderClear(Renderer);
	//Draw menu
	time1++;
	Intro.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, in, NULL, &rc);
	if (time1 >= 200)
	{
		intro = true;
	}
	//Update screen
	SDL_RenderPresent(Renderer);
	SDL_Delay(10);	// 1000/10 = 100 fps max
	SDL_Event mouse;
	SDL_PollEvent(&mouse);

}


void Game::playMusicMenu()
{
	audio.PlayMusic("gamemus.ogg", 2.0f);
}
void Game::playMusicGame()
{
	audio.PlayMusic("gamemus.ogg", 2.0f);
}
void Game::playMusicEnd()
{
	audio.PlayMusic("", 1.0f);
}

void Game::OpenMenu()
{
	SDL_Rect rc;
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	//Clear rendering target
	SDL_RenderClear(Renderer);
	//Draw menu
	Menu.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, menu, NULL, &rc);
	//Update screen
	SDL_RenderPresent(Renderer);
	SDL_Delay(10);	// 1000/10 = 100 fps max
	SDL_Event mouse;
	SDL_PollEvent(&mouse);
	if (mouse.type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x >= 144*6 && x <= 174*6 && y >= 107*6 && y <= 120*6) {
			gameReady = true;
		}
	}
}

bool Game::CheckCollision(SDL_Rect* A, SDL_Rect* B)
{
	SDL_bool Collision = SDL_HasIntersection(A, B);
	if (Collision)
	{
		return true;
	}
	else
		return false;
}

void Game::timer() {
	SDL_Rect rc;
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	//Clear rendering target
	SDL_RenderClear(Renderer);
	//Draw menu

	Scene.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, img_background, NULL, &rc);
	Pause.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, pause, NULL, &rc);
	p.Render(Renderer);

	//Update screen
	SDL_RenderPresent(Renderer);
	SDL_Delay(3000);    // 1000/10 = 100 fps ma
}


void Game::Draw()
{
	p.Gravity();
	Scene.Move(-1, 0);
	if (Scene.GetX() <= -Scene.GetWidth())	Scene.SetX(0);

	TowD1.Move(-1, 0);
	if (TowD1.GetX() <= -TowD1.GetWidth())
	{
		TowD1.SetX(1920);
		posYD1 = rand() % 400 + 550;
		TowD1.SetY(posYD1);
	}
	TowD2.Move(-1, 0);
	if (TowD2.GetX() <= -TowD2.GetWidth())
	{
		TowD2.SetX(1920);
		posYD2 = rand() % 400 + 550;
		TowD2.SetY(posYD2);
	}
	TowD3.Move(-1, 0);
	if (TowD3.GetX() <= -TowD3.GetWidth())
	{
		TowD3.SetX(1920);
		posYD3 = rand() % 400 + 550;
		TowD3.SetY(posYD3);
	}

	TowU1.Move(-1, 0);
	if (TowU1.GetX() <= -TowU1.GetWidth())
	{
		TowU1.SetX(1920);
		TowU1.SetY(posYD1 - 950);
	}
	TowU2.Move(-1, 0);
	if (TowU2.GetX() <= -TowU2.GetWidth())
	{
		TowU2.SetX(1920);
		TowU2.SetY(posYD2 - 950);
	}
	TowU3.Move(-1, 0);
	if (TowU3.GetX() <= -TowU3.GetWidth())
	{
		TowU3.SetX(1920);
		TowU3.SetY(posYD3 - 950);
	}

	Egg1.Move(-1, 0);
	if (Egg1.GetX() <= -Egg1.GetWidth())
	{
		Egg1.SetX(1920 + (59 * 3) - 50);
		Egg1.SetY(rand() % 300 + 200);
		e1 = true;
		e1prob = rand() % 3;
	}
	Egg2.Move(-1, 0);
	if (Egg2.GetX() <= -Egg2.GetWidth())
	{
		Egg2.SetX(1920 + (59 * 3) - 50);
		Egg2.SetY(rand() % 300 + 200);
		e2 = true;
		e2prob = rand() % 2;
	}
	Egg3.Move(-1, 0);
	if (Egg3.GetX() <= -Egg3.GetWidth())
	{
		Egg3.SetX(1920 + (59 * 3) - 50);
		Egg3.SetY(rand() % 300 + 200);
		e3 = true;
		e3prob = rand() % 4;
	}
	
	SDL_Rect rc;
	SDL_Rect pl;
	SDL_Rect d1;
	SDL_Rect d2;
	SDL_Rect d3;
	SDL_Rect u1;
	SDL_Rect u2;
	SDL_Rect u3;
	SDL_Rect re1;
	SDL_Rect re2;
	SDL_Rect re3;

	for (int i = 0; i < MAX_SHOTS; ++i)
	{
		if (Shots[i].IsAlive())
		{
			Shots[i].Move(1, 0);
			if (Shots[i].GetX() > WINDOW_WIDTH)	Shots[i].ShutDown();
		}
	}
	
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	if (god_mode) SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
	//Clear rendering target
	SDL_RenderClear(Renderer);
	//Draw scene
	Scene.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, img_background, NULL, &rc);
	rc.x += rc.w;
	SDL_RenderCopy(Renderer, img_background, NULL, &rc);

	TowD1.GetRect(&d1.x, &d1.y, &d1.w, &d1.h);
	SDL_RenderCopy(Renderer, towd, NULL, &d1);
	TowD2.GetRect(&d2.x, &d2.y, &d2.w, &d2.h);
	SDL_RenderCopy(Renderer, towd, NULL, &d2);
	TowD3.GetRect(&d3.x, &d3.y, &d3.w, &d3.h);
	SDL_RenderCopy(Renderer, towd, NULL, &d3);

	TowU1.GetRect(&u1.x, &u1.y, &u1.w, &u1.h);
	SDL_RenderCopy(Renderer, towu, NULL, &u1);
	TowU2.GetRect(&u2.x, &u2.y, &u2.w, &u2.h);
	SDL_RenderCopy(Renderer, towu, NULL, &u2);
	TowU3.GetRect(&u3.x, &u3.y, &u3.w, &u3.h);
	SDL_RenderCopy(Renderer, towu, NULL, &u3);

	if (e1 && e1prob >= 1)
	{
		Egg1.GetRect(&re1.x, &re1.y, &re1.w, &re1.h);
		SDL_RenderCopy(Renderer, egg1, NULL, &re1);
	}
	if (e2 && e2prob == 1)
	{
		Egg2.GetRect(&re2.x, &re2.y, &re2.w, &re2.h);
		SDL_RenderCopy(Renderer, egg2, NULL, &re2);
	}
	if (e3 && e3prob == 1)
	{
		Egg3.GetRect(&re3.x, &re3.y, &re3.w, &re3.h);
		SDL_RenderCopy(Renderer, egg3, NULL, &re3);
	}

	p.GetCollider(&pl.x, &pl.y, &pl.w, &pl.h);


	//Draw player
	if (!dead)
	{
		p.Render(Renderer);
	}
	else
	{
		p.RenderDead(Renderer);
	}
	if (god_mode)
	{
		SDL_RenderDrawRect(Renderer, &pl);
		SDL_RenderDrawRect(Renderer, &d1);
		SDL_RenderDrawRect(Renderer, &d2);
		SDL_RenderDrawRect(Renderer, &d3);
		SDL_RenderDrawRect(Renderer, &u1);
		SDL_RenderDrawRect(Renderer, &u2);
		SDL_RenderDrawRect(Renderer, &u3);
		SDL_RenderDrawRect(Renderer, &re1);
		SDL_RenderDrawRect(Renderer, &re2);
		SDL_RenderDrawRect(Renderer, &re3);
	}

	SDL_bool collisionE1 = SDL_HasIntersection(&pl, &re1);
	SDL_bool collisionE2 = SDL_HasIntersection(&pl, &re2);
	SDL_bool collisionE3 = SDL_HasIntersection(&pl, &re3);
	SDL_bool collisionD1 = SDL_HasIntersection(&pl, &d1);
	SDL_bool collisionD2 = SDL_HasIntersection(&pl, &d2);
	SDL_bool collisionD3 = SDL_HasIntersection(&pl, &d3);
	SDL_bool collisionU1 = SDL_HasIntersection(&pl, &u1);
	SDL_bool collisionU2 = SDL_HasIntersection(&pl, &u2);
	SDL_bool collisionU3 = SDL_HasIntersection(&pl, &u3);

	if (collisionD1 ||collisionD2 || collisionD3 || collisionU1 || collisionU2 || collisionU3)
	{
		if (!god_mode)
		{
			dead = true;
		}
	/*	play = true;*/
	}
	if (collisionE1 && e1)
	{
		points += 100;
		egg1count++;
		e1 = false;
	}
	if (collisionE2 && e2)
	{

		points += 200;
		egg2count++;
		e2 = false;

	}
	if (collisionE3 && e3)
	{
		points += 300;
		egg3count++;
		e3 = false;
	}
	time3++;
	if (time3 >= 50)
	{
		points += 5;
		time3 = 0;
	}

	std::string s = "Score: " + std::to_string(points);
	Text(s.c_str(), 40, 30, 255, 255, 255);
	Text(std::to_string(egg1count).c_str(), 100, 100, 255, 255, 255);
	Text(std::to_string(egg2count).c_str(), 100, 150, 255, 255, 255);
	Text(std::to_string(egg3count).c_str(), 100, 200, 255, 255, 255);
	SDL_Rect egc1;
	SDL_Rect egc2;
	SDL_Rect egc3;
	Eggc1.GetRect(&egc1.x, &egc1.y, &egc1.w, &egc1.h);
	Eggc2.GetRect(&egc2.x, &egc2.y, &egc2.w, &egc2.h);
	Eggc3.GetRect(&egc3.x, &egc3.y, &egc3.w, &egc3.h);
	SDL_RenderCopy(Renderer, egg1c, NULL, &egc1);
	SDL_RenderCopy(Renderer, egg2c, NULL, &egc2);
	SDL_RenderCopy(Renderer, egg3c, NULL, &egc3);

	//Draw shots
	/*for (int i = 0; i < MAX_SHOTS; ++i)
	{
		if (Shots[i].IsAlive())
		{
			Shots[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderCopy(Renderer, img_shot, NULL, &rc);
		}
	}*/

	int Ypos = p.Ypo();
	if (Ypos >= 1000 || Ypos <= 0)
	{
		play = true;
	}

	//Update screen
	SDL_RenderPresent(Renderer);
	SDL_Delay(10);	// 1000/10 = 100 fps max
}

void Game::OpenEnd()
{
	SDL_Rect rc;
	//Set the color used for drawing operations
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	//Clear rendering target
	SDL_RenderClear(Renderer);
	//Draw end
	EndMenu.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, endmenu, NULL, &rc);
	//Update screen
	std::string s = "Score: " + std::to_string(points);
	Text(s.c_str(), 850, 600, 205, 146, 44);
	SDL_RenderPresent(Renderer);
	SDL_Delay(10);	// 1000/10 = 100 fps max

	SDL_Event mouse;
	SDL_PollEvent(&mouse);
	if (mouse.type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x >= 144*6 && x <= 174*6 && y >= 116*6 && y <= 144*6) {
			end = true;
		}
	}
}

void Game::Text(const char* msg, int x, int y, int r, int g, int b) 
{
	SDL_Surface* surf;
	SDL_Texture* tex;
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	SDL_Rect rect;
	surf = TTF_RenderText_Solid(font, msg, color);
	tex = SDL_CreateTextureFromSurface(Renderer, surf);
	rect.x = x;
	rect.y = y;
	if (surf != nullptr)
	{
		rect.w = surf->w;
		rect.h = surf->h;
	}
	SDL_FreeSurface(surf);
	SDL_RenderCopy(Renderer, tex, NULL, &rect);
}
