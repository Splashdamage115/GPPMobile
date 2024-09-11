#include "Source.h"

float Game::deltaTime = 0.f;

Game::Game() : 
	m_window{ sf::VideoMode{ 1920, 1080, 32U }, "Candy Cronch"/*, sf::Style::Fullscreen*/ }
{
}

void Game::init()
{

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

	m_window.display();
}

void Game::events()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}

}

void Game::update()
{
}
