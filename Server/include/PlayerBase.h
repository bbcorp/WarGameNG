#ifndef PLAYERBASE_H
#define PLAYERBASE_H
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <asio.hpp>
#include "../../Client/include/wargame_generated.h"

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

	void receiveDamage(uint16_t damage);
	std::string encodeFlatBuf(void);
	std::string m_name;
	asio::ip::udp::endpoint m_sender_enpoint;
protected:
	int16_t m_id;
	uint16_t m_health;
	uint16_t m_ammo;
	sf::Vector2u m_pos;
	uint16_t m_orientation;
	uint16_t m_state;
};

#endif