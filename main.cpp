#include "Game.h"


int main(int argc, char* args[])
{
	double first, last = 0;

	Game game;
	if (!game.Init()) return -1;

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
		game.gameReady = game.Update();
		game.Draw();
	}
	

	/*while (!game.gameReady)
	{
		game.gameReady = game.Update();
		game.Draw();
	}*/
	while (!game.end)
	{
		game.end = game.Update();
		game.Draw();
	}

	game.Release();
	return 0;
}