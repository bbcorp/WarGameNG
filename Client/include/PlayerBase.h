#ifndef PLAYERBASE_H
#define PLAYERBASE_H
#include <SFML/Graphics/Rect.hpp>
#include <string>

class PlayerBase
{
public:
	PlayerBase(void);
	PlayerBase(std::string name);
	void receiveDamage(uint16_t damage);
	std::string m_name;
	uint16_t m_orientation;
	uint16_t m_state;
protected:
	int16_t m_id;
	uint16_t m_health;
	uint16_t m_ammo;
	sf::Vector2u m_pos;
};

#endif