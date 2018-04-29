#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H
#include "Player.h"
#include "Bullet.h"

typedef enum e_wallPosition
{
	WALL_NONE = 0,
	WALL_LEFTRIGHT = 1,
	WALL_UPDOWN = 2,
	WALL_BOTH = 3
} t_wallPosition;

class MainPlayer : public Player
{
public:
	MainPlayer();
	MainPlayer(std::string name);
	void move(int16_t x, int16_t y);
	void fire(uint16_t x, uint16_t y);

	sf::View m_PlayerView;
	std::vector<Player> m_ennemiesPlayers;
	std::vector<engine::Bullet> m_bulletQueue;
	std::vector<engine::Bullet> m_bullets;

private:
	void nearWallMode(int16_t x, int16_t y);
	bool checkWallsCollision(int16_t x, int16_t y);
	bool checkPlayersCollision(int16_t x, int16_t y);

	sf::FloatRect m_PlayerViewRect;
	std::vector<sf::FloatRect> m_wallRects;
};

#endif