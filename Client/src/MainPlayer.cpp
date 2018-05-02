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
#include <iostream>

using namespace std;

MainPlayer::MainPlayer() : Player(), m_PlayerViewRect(0, 0, 800, 600)
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
}

MainPlayer::MainPlayer(string name) : Player(name), m_PlayerViewRect(0, 0, 800, 600)
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
}

void MainPlayer::move(int16_t x, int16_t y)
{
	if (checkWallsCollision(x, y) || checkPlayersCollision(x, y))
		return;
	m_sprite.move(x, y);
	nearWallModeMove(x, y);
	m_pos.x += x;
	m_pos.y += y;
}

void MainPlayer::fire(uint16_t x, uint16_t y)
{
	sf::Vector2f view(m_PlayerView.getCenter());
	view.x -= m_PlayerViewRect.width / 2;
	view.y -= m_PlayerViewRect.height / 2;
	uint16_t mousePosX(x + view.x);
	uint16_t mousePosY(y + view.y);
	engine::Bullet o_bullet(m_pos.x + 16, m_pos.y + 16, mousePosX, mousePosY, m_id);
	m_bulletQueue.push_back(o_bullet);
}

bool MainPlayer::checkWallsCollision(int16_t x, int16_t y)
{
	std::vector<sf::FloatRect> walls(engine::Map::getWalls());
	for (uint16_t i = 0; i < walls.size(); i++)
	{
		if (walls.at(i).intersects(sf::FloatRect(m_pos.x + x, m_pos.y + y, 30, 30)))
			return true;
	}
	return false;
}

bool MainPlayer::checkPlayersCollision(int16_t x, int16_t y)
{
	for (uint16_t i = 0; i < m_ennemiesPlayers.size(); i++)
	{
		sf::FloatRect ennemyRect(m_ennemiesPlayers.at(i).m_pos.x, m_ennemiesPlayers.at(i).m_pos.y, 30, 30);
		if (ennemyRect.intersects(sf::FloatRect(m_pos.x + x, m_pos.y + y, 30, 30)))
			return true;
	}
	return false;
}

void MainPlayer::nearWallModeMove(int16_t x, int16_t y)
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

uint16_t MainPlayer::nearWallMode(void)
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
	return wallPosition;
}

void MainPlayer::updatePosition(uint16_t x, uint16_t y)
{
	m_pos.x = x;
	m_pos.y = y;
	m_sprite.setPosition({ (float)m_pos.x, (float)m_pos.y });
	m_PlayerViewRect.left = x - m_PlayerViewRect.width / 2 + 16;
	m_PlayerViewRect.top = y - m_PlayerViewRect.height / 2 + 16;
	m_PlayerView.reset(m_PlayerViewRect);
}