#ifndef PLAYERBASE_H
#define PLAYERBASE_H
//#include <SDL_config.h>
//#include <SDL_rect.h>
#include <string>
#include "Player.h"

class PlayerBase : public Player
{
public:
	PlayerBase(void);
	PlayerBase(std::string nom);
	void receiveDamage(uint16_t damage);
	void displayName2(void);
private:
	int16_t m_id;
	std::string m_name;
	uint16_t m_health;
	uint16_t m_ammo;
	uint16_t m_state;
	uint16_t m_orientation;
	sf::IntRect m_pos;
};

#endif