#include "Player.h"
#include "Game.h"

Game game;

void Player::Render(SDL_Renderer* ren)
{

	animationTimer++;
	if (animationTimer < 16)
	{
		SDL_RenderCopyEx(ren, getTexture(), &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
	else if (animationTimer >= 16 && animationTimer <= 32)
	{
		SDL_RenderCopyEx(ren, Tex1, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
	else if (animationTimer >= 32 && animationTimer <= 48)
	{
		SDL_RenderCopyEx(ren, Tex2, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
	else if (animationTimer > 48)
	{
		SDL_RenderCopyEx(ren, Tex1, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
	}
	if (animationTimer > 54)
	{
		animationTimer = 0;
	}
	
}

void Player::RenderDead(SDL_Renderer* ren)
{
	SDL_RenderCopyEx(ren, Tex3, &getSrc(), &getDest(), 0, NULL, SDL_FLIP_NONE);
}

void Player::Gravity()
{

	if (JumpState())
	{
		accelerator1 += 0.035;
		accelerator2 += 0.035;
		jumpHeight += gravity;
		Ypos += gravity + accelerator1 + accelerator2 + jumpHeight;
		setDest(200, Ypos, 60*3, 46 * 3);
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
		setDest(200, Ypos, 60*3, 46*3);
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


void Player::CreateTexture1(const char* address, SDL_Renderer* ren)
{
	Tex1 = TextureManager::Texture(address, ren);
}

void Player::CreateTexture2(const char* address, SDL_Renderer* ren)
{
	Tex2 = TextureManager::Texture(address, ren);
}

void Player::CreateTexture3(const char* address, SDL_Renderer* ren)
{
	Tex3 = TextureManager::Texture(address, ren);
}

