#include "Game.h"

int main(int argc, char* args[])
{
	double first, last = 0;

	Game game;
	if (!game.Init()) return -1;

	bool end = false;
	while (!end)
	{
		end = game.Update();
		game.Draw();
		/*first = SDL_GetTicks();
		if (first - last < 16.7)
		{
			SDL_Delay(16.7 - (first - last));
		}
		last = first;*/
	}

	game.Release();
	return 0;
}