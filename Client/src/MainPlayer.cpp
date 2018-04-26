#include "../include/MainPlayer.h"

using namespace std;

MainPlayer::MainPlayer() : Player(), m_PlayerViewRect(400, 500, 800, 600)
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

MainPlayer::MainPlayer(string name) : Player(name), m_PlayerViewRect(400, 500, 800, 600)
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
	nearWallMode(x, y);
	m_pos.x += x;
	m_pos.y += y;
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