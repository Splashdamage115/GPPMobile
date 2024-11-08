// David Strikaitis c00283152
#ifndef GAME_H
#define GAME_H

#include "Resources.h"
#include "canvas.h"
#include "ColourPicker.h"

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

	std::shared_ptr<Canvas> m_canvas;
	std::shared_ptr<ColourPicker> m_colourPicker;
};

#endif // !GAME_H
