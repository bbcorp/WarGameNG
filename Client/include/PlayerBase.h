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
protected:
	int16_t m_id;
	uint16_t m_health;
	uint16_t m_ammo;
	uint16_t m_state;
	uint16_t m_orientation;
	sf::IntRect m_pos;
};

#endif