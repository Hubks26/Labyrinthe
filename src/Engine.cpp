#include "Engine.h"

const sf::Time Engine::m_timePerFrame = sf::seconds(1.f/600.f);

Engine::Engine()
: m_window(sf::VideoMode(1000, 1000), "Labirynth", sf::Style::Fullscreen)
, m_lab()
{
}

void Engine::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > m_timePerFrame)
		{
			timeSinceLastUpdate -= m_timePerFrame;
			update();
		}

		render();
	}
}

void Engine::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			m_window.close();
	}
}

void Engine::update()
{
	m_lab.update();
}

void Engine::render()
{
	m_window.clear();
	m_window.draw(m_lab);
	m_window.display();
}
