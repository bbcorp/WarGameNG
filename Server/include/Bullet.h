#ifndef BULLET_H
#define BULLET_H
#include <string>
#include <stdint.h>
#include <flatbuffers/flatbuffers.h>
#include "../../Client/include/wargame_generated.h"

namespace engine
{
	class Bullet
	{
	public:
		Bullet(const WarGame::fb::bullet *bullet);
		std::string encodeFlatBuf(void) const;
		std::string encodeFlatBufDelete(void) const;
		void calculateNextPixel(void);
		flatbuffers::Offset<WarGame::fb::bullet> returnStructFbBullet(flatbuffers::FlatBufferBuilder *builder);

		uint16_t m_id;
		uint16_t m_ownerId;
		uint16_t m_src_x;
		uint16_t m_src_y;
		uint16_t m_dst_x;
		uint16_t m_dst_y;
		uint16_t m_dX;
		uint16_t m_dY;
		int16_t m_err;
		int16_t m_sX;
		int16_t m_sY;
		uint16_t m_w;
		uint16_t m_h;

	private:

	};
}
#endif