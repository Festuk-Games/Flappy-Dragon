#pragma once
#include "Object.h"

class Player :public Object
{
private:
	double gravity = 0.2;
	double Ypos = 256;
	double Xpos;
	double accelerator1 = 0;
	double accelerator2 = 0;
	bool inJump = false;
	double jumpHeight = -10;
	double jumpTimer;
	double lastJump = 0;

	int incY1 = 0;
	int pipeDistance1 = 400;
	int x, y;
	int width, height;

	int animationTimer;
	SDL_Texture* Tex1;
	SDL_Texture* Tex2;
public:
	void Gravity();
	void GetJumpTime();
	void Jump();
	int Ypo();
	int Xpo();
	bool JumpState();
	void Render(SDL_Renderer* ren);

	void CreateTexture1(const char* address, SDL_Renderer* ren);
	void CreateTexture2(const char* address, SDL_Renderer* ren);

	bool PipeUpdate(int incY, int& score);
	int getPipe1X();
	int getPipe1Y();
};