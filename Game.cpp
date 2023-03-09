#include "Game.h"
#include <math.h>
#include <iostream>
#define OGG_MUSIC

using namespace std;
Mix_Music* gMusic = NULL;

int i = 0;

Game::Game() {
	Window = NULL;
	Renderer = NULL;
	GameState = false;
	TTF_Init();
	//sprite dimension
	p.setSource(0,0,217,218);
	//Pipe.setSource(0, 0, 217, 218);
	//destination dimension
	p.setDest(100, 200, 100, 100);
	//Pipe.setDest(100, 200, 400, 400);
	loadMedia();
}
Game::~Game(){}

bool Game::getGameState()
{
	return  GameState;
}


bool Game::Init()
{
	//Initialize SDL with all subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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
		shot.CreateTexture("shot.png", Renderer);
	}
	//Initialize keys array
	for (int i = 0; i < MAX_KEYS; ++i)
		keys[i] = KEY_IDLE;

	//Load images
	if (!LoadImages())
		return false;

	//Init variables
	//size: 104x82
	Player.Init(20, WINDOW_HEIGHT >> 1, 104, 82, 5);
	idx_shot = 0;
	int w;
	SDL_QueryTexture(menu, NULL, NULL, &w, NULL);
	Menu.Init(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 4);
	SDL_QueryTexture(endmenu, NULL, NULL, &w, NULL);
	EndMenu.Init(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 4);
	SDL_QueryTexture(img_background, NULL, NULL, &w, NULL);
	Scene.Init(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 4);
	SDL_QueryTexture(towd, NULL, NULL, &w, NULL);
	TowD1.Init(500, 600, 100, 600, 4);
	TowD2.Init(1100, 600, 100, 600, 4);
	TowD3.Init(1750, 650, 100, 600, 4);
	font = TTF_OpenFont("Fonts/calibrib.ttf", 32);
	return true;
}


bool Game::loadMedia()
{
	bool success = true;
	//Load music
	gMusic = Mix_LoadMUS("gamemus.ogg");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		
	}
	return success;
}



bool Game::LoadImages()
{
	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_Log("IMG_Init, failed to init required png support: %s\n", IMG_GetError());
		return false;
	}
	menu = SDL_CreateTextureFromSurface(Renderer, IMG_Load("button.png"));
	if (menu == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	endmenu = SDL_CreateTextureFromSurface(Renderer, IMG_Load("end.jpg"));
	if (endmenu == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	img_background = SDL_CreateTextureFromSurface(Renderer, IMG_Load("fondo.png"));
	if (img_background == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	towd = SDL_CreateTextureFromSurface(Renderer, IMG_Load("pipe.png"));
	if (towd == NULL) {
		SDL_Log("CreateTextureFromSurface failed: %s\n", SDL_GetError());
		return false;
	}
	img_shot = SDL_CreateTextureFromSurface(Renderer, IMG_Load("shot.png"));
	if (img_shot == NULL) {
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
	SDL_DestroyTexture(img_player);
	SDL_DestroyTexture(img_shot);
	SDL_DestroyTexture(towd);
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

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
	if (event.type == SDL_MOUSEMOTION)
	{
		cout << event.motion.x << "  " << event.motion.y << endl;
	}
	if (event.type == SDL_MOUSEBUTTONDOWN && event.motion.x <= 5 && event.motion.x >= 5 && event.motion.y <= 5 && event.motion.y >= 5)
	{
		cout << "Pressed" << endl;
	}
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
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
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)	Release();
	if (keys[SDL_SCANCODE_F1] == KEY_DOWN)		god_mode = !god_mode;
	if (keys[SDL_SCANCODE_UP] == KEY_REPEAT)	fy = -1;
	if (keys[SDL_SCANCODE_DOWN] == KEY_REPEAT)	fy = 1;
	if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT)	fx = -1;
	if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT)	fx = 1;
	if (keys[SDLK_LCTRL] == KEY_DOWN)
	{
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(gMusic, -1);
		}
		//If music is being played
		else
		{
			//If the music is paused
			if (Mix_PausedMusic() == 1)
			{
				//Resume the music
				Mix_ResumeMusic();
			}
			//If the music is playing
			else
			{
				//Pause the music
				Mix_PauseMusic();
			}
		}
		points += 1;
		//get player ypos
		int Ypos = p.Ypo();
		//size: 56x20
		//offset from player: dx, dy = [(29, 3), (29, 59)]
		Shots[idx_shot].Init(360, Ypos+100, 56, 20, 10);
		idx_shot++;
		idx_shot %= MAX_SHOTS;
	}
	/*p.Xpo() >= Pipe.Xpo() && p.Xpo() <= Pipe.Xpo()*/
	SDL_Rect pos;

	
	//if (p.Ypo() <= Pipe.Ypo() && p.getDest() >= Pipe.getDest())
	//{
	//	points++;
	//}

	return false;

}


//void Game::CollisionDetection()
//{
//	/*if (Collision::CheckCollision(&p.getDest(), &Pipe.getDest()))
//	{
//		points += 1;
//	}*/
//	//else if (Collision::CheckCollision(&p.getDest(), &ground1.getDest()) || CollisionManager::CheckCollision(&p.getDest(), &ground2.getDest()) || p.getYpos() < 0)
//	//{
//	//	SDL_Delay(500);
//	//	list.Insert(points, generations);
//	//	generations++;
//	//	neuralNetwork.SaveProgress("Progress.txt", generations);
//	//	Reset();
//	//}
//}


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
		if (x >= 865 && x <= 1055 && y >= 680 && y <= 760) {
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

void Game::Draw()
{
	p.Gravity();
	Scene.Move(-1, 0);
	if (Scene.GetX() <= -Scene.GetWidth())	Scene.SetX(0);
	TowD1.Move(-1, 0);
	if (TowD1.GetX() <= -TowD1.GetWidth())	TowD1.SetX(1920);
	TowD2.Move(-1, 0);
	if (TowD2.GetX() <= -TowD2.GetWidth())	TowD2.SetX(1920);
	TowD3.Move(-1, 0);
	if (TowD3.GetX() <= -TowD3.GetWidth())	TowD3.SetX(1920);

	SDL_Rect rc;
	SDL_Rect d1;
	SDL_Rect d2;
	SDL_Rect d3;
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
	//Pipe.Render(Renderer);
	SDL_bool collision1 = SDL_HasIntersection(&p.getDest(), &d1);
	SDL_bool collision2 = SDL_HasIntersection(&p.getDest(), &d2);
	SDL_bool collision3 = SDL_HasIntersection(&p.getDest(), &d3);
	if (collision1 ||collision2 || collision3)
	{
		points-=5;
	}
	else
	{
		points++;
	}

	//Draw player
	p.Render(Renderer);
	//CheckCollision(&p.getDest(), &Pipe.getDest());
	std::string s = "Score: " + std::to_string(points);
	Text(s.c_str(), 20, 30, 0, 255, 0);


	//Draw shots
	for (int i = 0; i < MAX_SHOTS; ++i)
	{
		if (Shots[i].IsAlive())
		{
			Shots[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderCopy(Renderer, img_shot, NULL, &rc);
		}
	}
	int Ypos = p.Ypo();
	if (Ypos >= 800 || Ypos <= -50)
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
		if (x >= 865 && x <= 1055 && y >= 680 && y <= 760) {
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
	rect.w = surf->w;
	rect.h = surf->h;
	SDL_FreeSurface(surf);
	SDL_RenderCopy(Renderer, tex, NULL, &rect);
	SDL_DestroyTexture(tex);
}
