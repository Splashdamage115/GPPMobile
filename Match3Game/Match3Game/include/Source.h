#include <iostream>
#include <SFML/Graphics.hpp>

#include <time.h> 
#include <fstream>


class Game
{
public:
	Game();

	void init();

	void run();

	static float deltaTime;

private:
	void render();
	void events();
	void update();

	sf::RenderWindow m_window;
};

