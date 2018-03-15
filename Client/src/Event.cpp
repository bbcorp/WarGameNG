#include "../include/Event.h"
#include "../include/sprite.h"


void engine::Event::handleEvents(sf::Window *window)
{
	while (window->pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		default:
			break;
		}
	}
}

void engine::Event::handleKeyboard(MainPlayer *o_MainPlayer)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		o_MainPlayer->m_state = WALK;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		o_MainPlayer->m_sprite.move(-1, -1);
		o_MainPlayer->m_orientation = UP_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		o_MainPlayer->m_sprite.move(1, -1);
		o_MainPlayer->m_orientation = UP_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		o_MainPlayer->m_sprite.move(0, -2);
		o_MainPlayer->m_orientation = UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		o_MainPlayer->m_sprite.move(-1, 1);
		o_MainPlayer->m_orientation = DOWN_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		o_MainPlayer->m_sprite.move(1, 1);
		o_MainPlayer->m_orientation = DOWN_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		o_MainPlayer->m_sprite.move(0, 2);
		o_MainPlayer->m_orientation = DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		o_MainPlayer->m_sprite.move(-2, 0);
		o_MainPlayer->m_orientation = LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		o_MainPlayer->m_sprite.move(2, 0);
		o_MainPlayer->m_orientation = RIGHT;
	}
}