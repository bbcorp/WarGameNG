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

#include "../include/MainPlayer.h"
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/ft_Delay.h"
#include "../include/sprite.h"

using namespace std;

MainPlayer::MainPlayer() : PlayerBase(), m_lastAnim(0), m_walkAnimationStep(0), m_deathAnimationStep(0), m_PlayerViewRect(400, 500, 800, 600)
{
	m_sprite.setTextureRect({ 1, 1, 32, 32 });
	m_sprite.setPosition({ (float)m_pos.x, (float)m_pos.y });
	m_PlayerView.reset(m_PlayerViewRect);

	sf::FloatRect wallLeft(0, 0, m_PlayerViewRect.width / 2 - 16, 1600);
	sf::FloatRect wallUp(0, 0, 1600, m_PlayerViewRect.height / 2 - 16);
	sf::FloatRect wallRight(1200 + 16, 0, m_PlayerViewRect.width / 2, 1600);
	sf::FloatRect wallDown(0, 1300 + 16, 1600, m_PlayerViewRect.height / 2);
	m_wallRects.push_back(wallLeft);
	m_wallRects.push_back(wallUp);
	m_wallRects.push_back(wallRight);
	m_wallRects.push_back(wallDown);
	m_clockUpdate = new sf::Clock;
	m_ennemy_texture = NULL;
}

MainPlayer::MainPlayer(string name) : PlayerBase(name), m_lastAnim(0),  m_walkAnimationStep(0), m_deathAnimationStep(0)
{
	m_sprite.setTextureRect({ 1, 1, 32, 32 });
	m_sprite.setPosition({ (float)m_pos.x, (float)m_pos.y });
	m_PlayerView.reset(m_PlayerViewRect);

	sf::FloatRect wallLeft(0, 0, m_PlayerViewRect.width / 2 - 16, 1600);
	sf::FloatRect wallUp(0, 0, 1600, m_PlayerViewRect.height / 2 - 16);
	sf::FloatRect wallRight(1200 + 16, 0, m_PlayerViewRect.width / 2, 1600);
	sf::FloatRect wallDown(0, 1300 + 16, 1600, m_PlayerViewRect.height / 2);
	m_wallRects.push_back(wallLeft);
	m_wallRects.push_back(wallUp);
	m_wallRects.push_back(wallRight);
	m_wallRects.push_back(wallDown);
	m_clockUpdate = new sf::Clock;
	m_ennemy_texture = NULL;
}

MainPlayer::~MainPlayer()
{
	if (m_ennemy_texture != NULL)
		delete m_ennemy_texture;
/*	delete m_clockUpdate; /!\ FIX ME /!\ */
}

MainPlayer::MainPlayer(const WarGame::fb::playerBase *pBase) : PlayerBase(pBase), m_lastAnim(0), m_walkAnimationStep(0), m_deathAnimationStep(0)
{	
	m_ennemy_texture = new sf::Texture;
	try {
		if (!m_ennemy_texture->loadFromFile("../res/ennemy.png"))
			throw string("Can't load ../res/ennemy.png");
	}
	catch (string const& exception)
	{
		cerr << exception << endl;
		sf::err();
		return;
	}
	m_ennemy_texture->setSmooth(true);
	m_sprite.setTexture(*m_ennemy_texture);

	m_sprite.setTextureRect({ 1, 1, 32, 32 });
	m_sprite.setPosition({ (float)m_pos.x, (float)m_pos.y });
	m_clockUpdate = new sf::Clock;
}


void MainPlayer::updateState(void)
{
	if (engine::ft_Delay(m_clockUpdate, sf::milliseconds(150)))
	{
		if (m_state == WALK)
		{
			if (m_walkAnimationStep < 3)
				m_walkAnimationStep++;
			else
				m_walkAnimationStep = 1;
			m_sprite.setTextureRect({ m_walkAnimationStep * 32 + m_walkAnimationStep + 1, m_orientation * 32 + m_orientation + 1, 32, 32 });
		}
		else
			m_sprite.setTextureRect({ 1, m_orientation * 32 + m_orientation + 1, 32, 32 });
	}
}

void MainPlayer::applyModificationFromNetwork(MainPlayer *o_player)
{
	m_sprite.setPosition(o_player->m_sprite.getPosition());
	m_pos = o_player->m_pos;
	m_orientation = o_player->m_orientation;
	m_state = o_player->m_state;
	m_health = o_player->getHealth();
	m_ammo = o_player->getAmmo();
}

void MainPlayer::move(int16_t x, int16_t y)
{
	m_sprite.move(x, y);
	nearWallMode(x, y);
	m_pos.x += x;
	m_pos.y += y;
}

void MainPlayer::nearWallMode(int16_t x, int16_t y)
{
	uint16_t wallPositionTmp1 = 0;
	uint16_t wallPositionTmp2 = 0;
	uint16_t wallPosition = 0;
	for (uint16_t i = 0; i < m_wallRects.size(); i++)
	{
		if (m_wallRects.at(i).intersects(sf::FloatRect(sf::Vector2f(m_pos), sf::Vector2f(32.0, 32.0))) && !(i % 2))
			wallPositionTmp1 = WALL_LEFTRIGHT;
		else if (m_wallRects.at(i).intersects(sf::FloatRect(sf::Vector2f(m_pos), sf::Vector2f(32.0, 32.0))) && i % 2)
			wallPositionTmp2 = WALL_UPDOWN;
	}
	wallPosition = wallPositionTmp1 + wallPositionTmp2;

	if (wallPosition == WALL_NONE)
		m_PlayerView.move(x, y);
	else if (wallPosition == WALL_UPDOWN)
		m_PlayerView.move(x, 0);
	else if (wallPosition == WALL_LEFTRIGHT)
		m_PlayerView.move(0, y);
	else
		return;
}