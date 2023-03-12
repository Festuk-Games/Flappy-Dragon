#include "Game.h"


int main(int argc, char* args[])
{

	double first, last = 0;

	Game game;
	Audio audio;

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
	if (!game.gameReady)
	{
		game.playMusicMenu();
	}
	while (!game.gameReady)
	{
		game.gameReady = game.Update();
		game.OpenMenu();
		
		if (game.timerReady)
		{
			game.playMusicGame();
			break;
		}
		if (game.gameReady)
		{
			game.play = false;
			break;
		}
		else if (game.close)
		{
			game.Release();
			return 0;
		}

	}
	while (game.timerReady)
	{
		game.timer();
		if (!game.play)
		{
			break;
		}
	}
	//if (!game.play)
	//{
	//	game.playMusicGame();
	//}
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