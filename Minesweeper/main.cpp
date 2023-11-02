#include "Game.h"

int main()
{
	Game* game = new Game(360, 360, easy);
	bool running = game->init();
	while (running)
	{
		// GameState state = game->run();
		// if (state == reset)
		//		game->reset()
		// else if (state == over)
		//		running = game->over()
		//
	}
	delete game;
	return 0;
}