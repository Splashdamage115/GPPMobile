#include <iostream>
#include <SFML/Graphics.hpp>

#include <time.h> 
#include <fstream>

#define SIZE_X 10
#define SIZE_Y 10

struct tile
{
	sf::Sprite body;
	sf::RectangleShape bounds;
	int typeNum;
};

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

	void rowFall(int t_xToFallTo, int t_yToFallTo);

	sf::RenderWindow m_window;

	tile m_tiles[SIZE_X][SIZE_Y];

	int selected = -1;

	sf::Texture m_textures[3];
	sf::Vector2f m_mousePos;

	sf::Text m_scoreText;
	sf::Font m_font;

	int m_score{ 0 };
};

