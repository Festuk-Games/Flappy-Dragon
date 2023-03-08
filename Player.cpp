#include "Player.h"
#include "Game.h"

Game game;

void Player::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), &getSrc(), &getDest());
}

void Player::Gravity()
{

	if (JumpState())
	{
		accelerator1 += 0.035;
		accelerator2 += 0.035;
		jumpHeight += gravity;
		Ypos += gravity + accelerator1 + accelerator2 + jumpHeight;
		setDest(200, Ypos, 217, 218);
		if (jumpHeight > 0)
		{
			inJump = false;
			jumpHeight = -10;
		}
	}
	else
	{
		accelerator1 += 0.035;
		accelerator2 += 0.035;
		Ypos += gravity + accelerator1 + accelerator2;
		setDest(200, Ypos, 217, 218);
	}
}

int Player::Ypo()
{
	return Ypos;
}

int Player::Xpo()
{
	return Xpos;
}

void Player::Jump()
{
	if (jumpTimer - lastJump > 180)
	{
		accelerator1 = 0;
		accelerator2 = 0;
		inJump = true;
		lastJump = jumpTimer;
	}
	else
	{
		Gravity();
	}
}

void Player::GetJumpTime()
{
	jumpTimer = SDL_GetTicks();
}

bool Player::JumpState()
{
	return inJump;
}
