#ifndef BULLET_H
#define BULLET_H
#include <string>
#include <stdint.h>
#include <SFML/System/Clock.hpp>
#include "../include/wargame_generated.h"

namespace engine
{
	class Bullet
	{
	public:
		Bullet(uint16_t src_x, uint16_t src_y, uint16_t dst_x, uint16_t dst_y, uint16_t ownerId);
		Bullet(const WarGame::fb::bullet *bullet);
		std::string encodeFlatBuf(void) const;
		static uint16_t getCurrentId(void);
		uint16_t m_id;
		uint16_t m_ownerId;
		uint16_t m_src_x;
		uint16_t m_src_y;
		uint16_t m_dst_x;
		uint16_t m_dst_y;
		uint16_t m_w;
		uint16_t m_h;
		static sf::Clock m_clock;

	private:
		static uint16_t m_idCount;

	};
}
#endif