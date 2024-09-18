#include "Source.h"

float Game::deltaTime = 0.f;

Game::Game() : 
	m_window{ sf::VideoMode{ 1920, 1080, 32U }, "Candy Cronch"/*, sf::Style::Fullscreen*/ }
{
}

void Game::init()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	m_font.loadFromFile(".\\ASSETS\\FONTS\\PixelSans.ttf");
	m_scoreText.setFont(m_font);
	m_scoreText.setPosition(900.f, 400.f);
	m_score = 0;
	m_scoreText.setString("Score:" + std::to_string(m_score));

	m_textures[0].loadFromFile(".\\ASSETS\\IMAGES\\Banana.png");
	m_textures[1].loadFromFile(".\\ASSETS\\IMAGES\\Cherries.png");
	m_textures[2].loadFromFile(".\\ASSETS\\IMAGES\\Pear.png");

	float scale = 2.0f;

	for (int x = 0; x < SIZE_X; x++)
	{
		for (int y = 0; y < SIZE_Y; y++)
		{
			m_tiles[x][y].typeNum = rand() % 3;

			m_tiles[x][y].body.setTexture(m_textures[m_tiles[x][y].typeNum]);
			m_tiles[x][y].body.setPosition(sf::Vector2f(x * 32.f * scale + 100.f, y * 32.f * scale + 100.f));

			m_tiles[x][y].bounds.setPosition(sf::Vector2f(x * 32.f * scale + 100.f, y * 32.f * scale + 100.f));
			m_tiles[x][y].bounds.setSize(sf::Vector2f(32.f * scale,32.f * scale));
			m_tiles[x][y].bounds.setFillColor(sf::Color::Transparent);
			m_tiles[x][y].bounds.setOutlineThickness(1.f);
			m_tiles[x][y].bounds.setOutlineColor(sf::Color::Transparent);

			m_tiles[x][y].body.setScale(scale, scale);
		}
	}
}

void Game::run()
{

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Clock clock;
	clock.restart();

	while (m_window.isOpen())
	{
		events();
		update();
		render();

		deltaTime = sf::Time::Zero.asMilliseconds();
	}

}

void Game::render()
{
	m_window.clear();

	for (int x = 0; x < SIZE_X; x++)
	{
		for (int y = 0; y < SIZE_Y; y++)
		{
			m_window.draw(m_tiles[x][y].bounds);
			m_window.draw(m_tiles[x][y].body);
		}
	}
	m_scoreText.setString("Score:" + std::to_string(m_score));
	m_window.draw(m_scoreText);
	m_window.display();
}

void Game::events()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();

		if (sf::Event::MouseMoved == event.type)
		{
			m_mousePos = sf::Vector2f((m_window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y))));
		}

		if (sf::Event::MouseButtonReleased == event.type)
		{
			for (int x = 0; x < SIZE_X; x++)
			{
				for (int y = 0; y < SIZE_Y; y++)
				{
					if (m_tiles[x][y].bounds.getGlobalBounds().contains(m_mousePos))
					{
						if (selected == -1)
						{
							selected = x + y * SIZE_Y;
							m_tiles[x][y].bounds.setOutlineColor(sf::Color::Yellow);
							std::cout << selected << std::endl;
						}
						else
						{
							std::cout << selected / SIZE_Y << ", " << selected % SIZE_Y << std::endl;

							{
								int newTile = m_tiles[x][y].typeNum;
								m_tiles[x][y].typeNum = m_tiles[selected % SIZE_X][selected / SIZE_X].typeNum;
								m_tiles[x][y].body.setTexture(m_textures[m_tiles[x][y].typeNum]);


								m_tiles[selected % SIZE_X][selected / SIZE_X].typeNum = newTile;
								m_tiles[selected % SIZE_X][selected / SIZE_X].body.setTexture(m_textures[m_tiles[selected % SIZE_X][selected / SIZE_X].typeNum]);


								m_tiles[selected % SIZE_X][selected / SIZE_X].bounds.setOutlineColor(sf::Color::Transparent);
								m_tiles[x][y].bounds.setOutlineColor(sf::Color::Transparent);

								selected = -1;
							}
						}
					}
				}
			}
		}
	}

}

void Game::update()
{
	for (int x = 0; x < SIZE_X; x++)
	{
		for (int y = 0; y < SIZE_Y; y++)
		{
			// check all to the right !
			if (m_tiles[x][y].typeNum == m_tiles[x + 1][y].typeNum && x + 1 < SIZE_X)
			{
				if (m_tiles[x][y].typeNum == m_tiles[x + 2][y].typeNum && x + 2 < SIZE_X)
				{
					rowFall(x, y);
					rowFall(x + 1, y);
					rowFall(x + 2, y);

					m_score += 3;
					/*m_tiles[x][0].typeNum = rand() % 3;
					m_tiles[x][0].body.setTexture(m_textures[m_tiles[x][0].typeNum]);

					m_tiles[x + 1][0].typeNum = rand() % 3;
					m_tiles[x + 1][0].body.setTexture(m_textures[m_tiles[x + 1][0].typeNum]);

					m_tiles[x + 2][0].typeNum = rand() % 3;
					m_tiles[x + 2][0].body.setTexture(m_textures[m_tiles[x + 2][0].typeNum]);*/
				}
			}

			if (m_tiles[x][y].typeNum == m_tiles[x][y + 1].typeNum && y + 1 < SIZE_Y)
			{
				if (m_tiles[x][y].typeNum == m_tiles[x][y + 2].typeNum && y + 2 < SIZE_Y)
				{
					rowFall(x, y);

					m_tiles[x][0].typeNum = rand() % 3;
					m_tiles[x][0].body.setTexture(m_textures[m_tiles[x][0].typeNum]);

					m_tiles[x][1].typeNum = rand() % 3;
					m_tiles[x][1].body.setTexture(m_textures[m_tiles[x][1].typeNum]);

					m_score += 3;

					//m_tiles[x][2].typeNum = rand() % 3;
					//m_tiles[x][2].body.setTexture(m_textures[m_tiles[x][2].typeNum]);
				}
			}
		}
	}
}

void Game::rowFall(int t_x, int t_yToFallTo)
{
	int lastTile = rand() % 3;
	for (int i = 0; i < t_yToFallTo + 1; i++)
	{
		int currentTile = m_tiles[t_x][i].typeNum;
		m_tiles[t_x][i].typeNum = lastTile;
		lastTile = currentTile;
		m_tiles[t_x][i].body.setTexture(m_textures[m_tiles[t_x][i].typeNum]);
	}
}
