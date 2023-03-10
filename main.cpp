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
			game.temporizador();
			game.play = false;
			break;
		}

	}
	if (!game.play)
	{
		game.playMusicGame();
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
		if (game.close)
		{
			game.Release();
			return 0;
		}
	}
	if (!game.end)
	{
		game.playMusicEnd();
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