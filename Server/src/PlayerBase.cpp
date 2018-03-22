#include "../include/PlayerBase.h"
#include <stdlib.h>
#include <iostream>

using namespace std;


PlayerBase::PlayerBase() : m_id(-1), m_health((uint16_t)100), m_ammo((uint16_t)30), m_state((uint16_t)0), m_orientation((uint16_t)0), m_pos(sf::Vector2u(384, 284))
{

}

PlayerBase::PlayerBase(string name) : m_name(name), m_id(-1), m_health((uint16_t)100), m_ammo((uint16_t)30), m_state((uint16_t)0), m_orientation((uint16_t)0), m_pos(384, 284)
{

}
PlayerBase::PlayerBase(const WarGame::fb::playerBase *pBase) : m_name(pBase->name()->data(), pBase->name()->size()), m_id(pBase->id()), m_health(pBase->health()), m_ammo(pBase->ammo()), m_state(pBase->state()), m_orientation(pBase->orientation()), m_pos(pBase->pos()->x(), pBase->pos()->y())
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

string PlayerBase::encodeFlatBuf(void)
{
	flatbuffers::FlatBufferBuilder builder;
	auto pBase = CreateplayerBaseDirect(builder, m_name.data(), m_id, m_health, m_ammo, m_orientation, m_state, &s_vector2u(m_pos.x, m_pos.y));
	builder.Finish(pBase);
	std::string buffer((char *)builder.GetBufferPointer(), (char *)builder.GetBufferPointer() + builder.GetSize());
	builder.ReleaseBufferPointer();
	return buffer;
}