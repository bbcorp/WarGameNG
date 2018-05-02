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

using namespace std;


PlayerBase::PlayerBase() : m_id(-1), m_pos(0, 0), m_health((uint16_t)100), m_orientation((uint16_t)0), m_state((uint16_t)0), m_ammo((uint16_t)30)
{

}

PlayerBase::PlayerBase(string name) : m_id(-1), m_name(name), m_pos(0, 0), m_health((uint16_t)100), m_orientation((uint16_t)0), m_state((uint16_t)0), m_ammo((uint16_t)30)
{

}
PlayerBase::PlayerBase(const WarGame::fb::playerBase *pBase) : m_name(pBase->name()->data(), pBase->name()->size()), m_id(pBase->id()), m_pos(pBase->pos()->x(), pBase->pos()->y()), m_health(pBase->health()), m_orientation(pBase->orientation()), m_state(pBase->state()), m_ammo(pBase->ammo())
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
		&& m_pos == Playerb.m_pos;
}

bool PlayerBase::operator!=(PlayerBase const& Playerb)
{
	return m_name != Playerb.m_name
		|| m_id != Playerb.m_id
		|| m_health != Playerb.m_health
		|| m_ammo != Playerb.m_ammo
		|| m_state != Playerb.m_state
		|| m_orientation != Playerb.m_orientation
		|| m_pos != Playerb.m_pos;
}

void PlayerBase::receiveDamage(uint16_t damage)
{
	if (m_health > 0)
		m_health -= damage;
	cout << m_health << endl;
}
using namespace WarGame::fb;

string PlayerBase::encodeFlatBuf(void) const
{
	flatbuffers::FlatBufferBuilder builder;
	s_vector2u pos(m_pos.x, m_pos.y);
	auto pBase = CreateplayerBaseDirect(builder, m_name.data(), m_id, m_health, m_ammo, m_orientation, m_state, &pos);
	FinishplayerBaseBuffer(builder, pBase);
	std::string buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
	builder.ReleaseBufferPointer();
	return buffer;
}

string PlayerBase::requestId(void) const
{
	flatbuffers::FlatBufferBuilder builder;
	auto request = CreaterequestIdDirect(builder, m_id, m_name.data(), 0, 0);
	FinishrequestIdBuffer(builder, request);
	std::string buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
	builder.ReleaseBufferPointer();
	return buffer;
}

uint16_t PlayerBase::getHealth(void) const
{
	return m_health;
}

uint16_t PlayerBase::getAmmo(void) const
{
	return m_ammo;
}