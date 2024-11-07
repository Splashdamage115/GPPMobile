// David Strikaitis c00283152
#ifndef GAME_H
#define GAME_H

#include "Resources.h"
#include "canvas.h"

class Game
{
public:
	Game();
	~Game();

	void Init();
	void Run();
private:
	void Update();
	void Render();

	Canvas m_canvas;
};

#endif // !GAME_H
