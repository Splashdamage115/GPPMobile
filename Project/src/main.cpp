#include "Game.h"

int main()
{
	SearchAndSetResourceDir("Project");

	Game game;
	game.Init();
	game.Run();
	return 0;
}