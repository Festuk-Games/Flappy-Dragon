#pragma once
#include "Object.h"

class Player :public Object
{
private:
	double gravity = 0.2;
	double Ypos = 256;
	double accelerator1 = 0;
	double accelerator2 = 0;
	bool inJump = false;
	double jumpHeight = -10;
	double jumpTimer;
	double lastJump = 0;

public:
	void Gravity();
	void GetJumpTime();
	void Jump();
	bool JumpState();
	void Render(SDL_Renderer* ren);
};