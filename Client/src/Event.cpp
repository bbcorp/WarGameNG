/*
* WarGame - small 2D game for studies
* Copyright (C) 2018  Bertrand Caplet <bbcorp@chunkz.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include "../include/Event.h"
#include "../include/sprite.h"
#include "../include/ft_Delay.h"
#include "../include/Bullet.h"
#include <iostream>
#include <stdlib.h>
#include <SFML/System/Clock.hpp>

using namespace std;

engine::Event::Event(sf::RenderWindow *window, MainPlayer *o_MainPlayer) : m_window(window), m_MainPlayer(o_MainPlayer)
{

}

void engine::Event::handleEvents(void)
{
		while (m_window->pollEvent(m_event))
		{
			switch (m_event.type)
			{
			case sf::Event::Closed:
				m_window->close();
				break;
			default:
				break;
			}
		}
		if (m_window->hasFocus())
			handleKeyboardGame();
}

void engine::Event::handleKeyboardGame(void)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_MainPlayer->setState(WALK);
		m_MainPlayer->updateState();
	}
	else
	{
		m_MainPlayer->setState(IDLE);
		m_MainPlayer->m_clockUpdate.restart();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_MainPlayer->move(-1, -1);
		m_MainPlayer->setOrientation(UP_LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_MainPlayer->move(1, -1);
		m_MainPlayer->setOrientation(UP_RIGHT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		m_MainPlayer->move(0, -2);
		m_MainPlayer->setOrientation(UP);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_MainPlayer->move(-1, 1);
		m_MainPlayer->setOrientation(DOWN_LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_MainPlayer->move(1, 1);
		m_MainPlayer->setOrientation(DOWN_RIGHT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_MainPlayer->move(0, 2);
		m_MainPlayer->setOrientation(DOWN);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_MainPlayer->move(-2, 0);
		m_MainPlayer->setOrientation(LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_MainPlayer->move(2, 0);
		m_MainPlayer->setOrientation(RIGHT);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && engine::ft_Delay(&engine::Bullet::m_clock, sf::milliseconds(350)))
	{
		m_MainPlayer->setState(FIRE);
		sf::Vector2i mousePos(sf::Mouse::getPosition(*m_window));
		m_MainPlayer->fire(mousePos.x, mousePos.y);
	}
}