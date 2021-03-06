#ifndef PLAYERBASE_H
#define PLAYERBASE_H
#include "../include/wargame_generated.h"
#include <SFML/Graphics/Rect.hpp>
#include <string>

typedef struct s_playerBase
{
	std::string name;
	uint16_t id;
	uint16_t health;
	uint16_t ammo;
	uint16_t orientation;
	uint16_t state;
	sf::Vector2u pos;
}t_playerBase;

class PlayerBase
{
public:
	PlayerBase(void);
	PlayerBase(std::string name);
	PlayerBase(const WarGame::fb::playerBase *pBase);
	bool operator==(PlayerBase const& Playerb);
	bool operator!=(PlayerBase const& Playerb);
	std::string encodeFlatBuf(void) const;
	std::string requestId(void) const;
	
	void receiveDamage(const uint16_t newHealth);
	bool setID(const int16_t newID);
	bool setOrientation(const uint16_t newOrientation);
	bool setState(const uint16_t newState);

	int16_t getID(void) const;
	uint16_t getHealth(void) const;
	uint16_t getAmmo(void) const;

	std::string m_name;
	sf::Vector2u m_pos;

protected:
	int16_t m_id;
	uint16_t m_health;
	uint16_t m_ammo;
	uint16_t m_orientation;
	uint16_t m_state;
	
};

#endif