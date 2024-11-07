// David Strikaitis c00283152
#include "Game.h"

int main()
{
	SearchAndSetResourceDir("Project");

	Game game;
	game.Init();
	game.Run();
	return 0;
}