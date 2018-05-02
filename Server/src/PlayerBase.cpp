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

#include "../include/PlayerBase.h"
#include <stdlib.h>
#include <iostream>
#include <SFML/System/Clock.hpp>

using namespace std;

PlayerBase::PlayerBase(const WarGame::fb::playerBase *pBase) : m_id(pBase->id()), m_name(pBase->name()->data(), pBase->name()->size()), m_pos(pBase->pos()->x(), pBase->pos()->y()), m_health(pBase->health()), m_orientation(pBase->orientation()), m_state(pBase->state()), m_ammo(pBase->ammo())
{

}

bool PlayerBase::operator==(PlayerBase const& Playerb)
{
	return m_name == Playerb.m_name
		&& m_id == Playerb.m_id
		&& m_health == Playerb.m_health
		&& m_ammo == Playerb.m_ammo
		&& m_state == Playerb.m_state
		&& m_orientation == Playerb.m_orientation
		&& m_pos == Playerb.m_pos
		&& m_sender_enpoint == Playerb.m_sender_enpoint;
}
bool PlayerBase::operator!=(PlayerBase const& Playerb)
{
	return m_name != Playerb.m_name
		|| m_id != Playerb.m_id
		|| m_health != Playerb.m_health
		|| m_ammo != Playerb.m_ammo
		|| m_state != Playerb.m_state
		|| m_orientation != Playerb.m_orientation
		|| m_pos != Playerb.m_pos
		|| m_sender_enpoint != Playerb.m_sender_enpoint;
}

void PlayerBase::receiveDamage(uint16_t damage)
{
	if (m_health > 0)
		m_health -= damage;
	cout << m_health << endl;
}

using namespace WarGame::fb;

flatbuffers::Offset<WarGame::fb::playerBase> PlayerBase::returnStructFbPlayerbase(flatbuffers::FlatBufferBuilder *builder)
{
	s_vector2u pos(m_pos.x, m_pos.y);
	flatbuffers::Offset<WarGame::fb::playerBase> pBase = CreateplayerBaseDirect(*builder, m_name.data(), m_id, m_health, m_ammo, m_orientation, m_state, &pos);
	return pBase;
}

string PlayerBase::encodeFlatBuf(void)
{
	flatbuffers::FlatBufferBuilder builder;
	s_vector2u pos(m_pos.x, m_pos.y);
	auto pBase = CreateplayerBaseDirect(builder, m_name.data(), m_id, m_health, m_ammo, m_orientation, m_state, &pos);
	FinishplayerBaseBuffer(builder, pBase);
	std::string buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
	builder.ReleaseBufferPointer();
	return buffer;
}