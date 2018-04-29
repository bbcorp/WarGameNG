/*
* WarGame - small 2D game for studies
* Copyright (C) 2018  Bertrand Caplet <bbcorp@chunkz.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include "../include/Bullet.h"
#include <flatbuffers/flatbuffers.h>
#include "../include/wargame_generated.h"

uint16_t engine::Bullet::m_idCount(0);
sf::Clock engine::Bullet::m_clock;

using namespace std;

engine::Bullet::Bullet(uint16_t src_x, uint16_t src_y, uint16_t dst_x, uint16_t dst_y, uint16_t ownerId) : m_id(getCurrentId()), m_ownerId(ownerId), m_src_x(src_x), m_src_y(src_y), m_dst_x(dst_x), m_dst_y(dst_y), m_w(6), m_h(6)
{

}

engine::Bullet::Bullet(const WarGame::fb::bullet *bullet) : m_id(bullet->id()), m_ownerId(bullet->ownerId()), m_src_x(bullet->src_x()), m_src_y(bullet->src_y()), m_dst_x(bullet->dst_x()), m_dst_y(bullet->dst_y()), m_w(bullet->w()), m_h(bullet->h())
{

}

using namespace WarGame::fb;

string engine::Bullet::encodeFlatBuf(void) const
{
	flatbuffers::FlatBufferBuilder builder;
	auto bullet = Createbullet(builder, m_id, m_ownerId, m_src_x, m_src_x, m_dst_x, m_dst_y, m_w, m_h);
	FinishbulletBuffer(builder, bullet);
	std::string buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
	builder.ReleaseBufferPointer();
	return buffer;
}

uint16_t engine::Bullet::getCurrentId(void)
{
	uint16_t currentId(m_idCount);
	m_idCount++;
	return currentId;
}