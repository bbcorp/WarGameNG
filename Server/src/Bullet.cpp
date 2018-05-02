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

using namespace std;


engine::Bullet::Bullet(const WarGame::fb::bullet *bullet) : m_id(bullet->id()), m_ownerId(bullet->ownerId()), m_src_x(bullet->src_x()), m_src_y(bullet->src_y()), m_dst_x(bullet->dst_x()), m_dst_y(bullet->dst_y()), m_w(bullet->w()), m_h(bullet->h())
{
	m_dX = abs(m_dst_x - m_src_x), m_sX = m_src_x < m_dst_x ? 1 : -1;
	m_dY = abs(m_dst_y - m_src_y), m_sY = m_src_y < m_dst_y ? 1 : -1;
	m_err = (m_dX > m_dY ? m_dX : -m_dY) / 2;
}

using namespace WarGame::fb;

string engine::Bullet::encodeFlatBuf(void) const
{
	flatbuffers::FlatBufferBuilder builder;
	auto bullet = Createbullet(builder, m_id, m_ownerId, m_src_x, m_src_y, m_dst_x, m_dst_y, m_w, m_h);
	FinishbulletBuffer(builder, bullet);
	std::string buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
	builder.ReleaseBufferPointer();
	return buffer;
}

string engine::Bullet::encodeFlatBufDelete(void) const
{
	flatbuffers::FlatBufferBuilder builder;
	auto deleteBullet = CreatedeleteBullet(builder, m_id, m_ownerId);
	FinishdeleteBulletBuffer(builder, deleteBullet);
	std::string buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
	builder.ReleaseBufferPointer();
	return buffer;
}

void engine::Bullet::calculateNextPixel(void)
{
	for (uint16_t i = 0; i < m_Clock.getElapsedTime().asMilliseconds()/2; i++)
	{
		if (m_err > -m_dX)
		{
			m_err -= m_dY;
			m_src_x += m_sX;
		}
		if (m_err < m_dY)
		{
			m_err += m_dX;
			m_src_y += m_sY;
		}
	}
	m_Clock.restart();
}


flatbuffers::Offset<WarGame::fb::bullet> engine::Bullet::returnStructFbBullet(flatbuffers::FlatBufferBuilder *builder)
{
	auto bullet = Createbullet(*builder, m_id, m_ownerId, m_src_x, m_src_y, m_dst_x, m_dst_y, m_w, m_h);
	return bullet;
}