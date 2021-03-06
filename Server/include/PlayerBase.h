#ifndef PLAYERBASE_H
#define PLAYERBASE_H
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
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
	PlayerBase(const WarGame::fb::playerBase *pBase);
	bool operator==(PlayerBase const& Playerb);
	bool operator!=(PlayerBase const& Playerb);
	void receiveDamage(uint16_t damage);
	flatbuffers::Offset<WarGame::fb::playerBase> returnStructFbPlayerbase(flatbuffers::FlatBufferBuilder *builder);
	std::string encodeFlatBuf(void);

	int16_t m_id;
	std::string m_name;
	sf::Vector2u m_pos;
	asio::ip::udp::endpoint m_sender_enpoint;
	sf::Clock m_clock;

private:
	uint16_t m_health;
	uint16_t m_orientation;
	uint16_t m_state;
	uint16_t m_ammo;
};

#endif