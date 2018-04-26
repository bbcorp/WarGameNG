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

#include "../include/Player.h"
#include "../include/GameEngine.h"
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/ft_Delay.h"
#include "../include/sprite.h"

using namespace std;



Player::Player() : PlayerBase(), m_lastAnim(0), m_walkAnimationStep(0), m_deathAnimationStep(0)
{
}

Player::Player(string name) : PlayerBase(name), m_lastAnim(0), m_walkAnimationStep(0), m_deathAnimationStep(0)
{
}

Player::Player(const WarGame::fb::playerBase *pBase) : PlayerBase(pBase), m_lastAnim(0), m_walkAnimationStep(0), m_deathAnimationStep(0)
{
	m_sprite.setTexture(*engine::Game::m_ennemy_texture);

	m_sprite.setTextureRect({ 1, 1, 32, 32 });
	m_sprite.setPosition({ (float)m_pos.x, (float)m_pos.y });
}

Player::~Player()
{
	/*	delete m_clockUpdate; /!\ FIX ME /!\ */
}


void Player::updateState(void)
{
	if (engine::ft_Delay(&m_clockUpdate, sf::milliseconds(150)))
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

void Player::applyModificationFromNetwork(Player *o_player)
{
	m_sprite.setPosition(o_player->m_sprite.getPosition());
	m_pos = o_player->m_pos;
	m_orientation = o_player->m_orientation;
	m_state = o_player->m_state;
	m_health = o_player->getHealth();
	m_ammo = o_player->getAmmo();
}