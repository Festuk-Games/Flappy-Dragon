#include "Game.h"

int main(int argc, char* args[])
{

	
	double first, last = 0;

	Game game;
	if (!game.Init()) return -1;

	while (!game.intro)
	{
		game.intro = game.Update();
		game.OpenIntro();

		if (game.intro)
		{
			game.gameReady = false;
			break;
		}

	}
	while (!game.gameReady)
	{
		game.gameReady = game.Update();
		game.OpenMenu();

		if (game.gameReady)
		{
			game.play = false;
			break;
		}

	}
	while (!game.play)
	{
		game.play = game.Update();
		game.Draw();
		if (game.play)
		{
			game.end = false;
			break;
		}
	}
	while (!game.end)
	{
		game.end = game.Update();
		game.OpenEnd();
		if (game.end)
		{
			game.Release();
			break;
		}
	}

	
	game.Release();
	return 0;
}